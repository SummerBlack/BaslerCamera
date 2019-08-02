#include "cameramanager.h"
#include <QDebug>
#include <QThread>
#include <QDir>
#include "baslerSDK/include/AutoPacketSizeConfiguration.h"

CameraManager *CameraManager::mInstance = new CameraManager;
CameraManager::CameraManager(QObject *parent) : QObject(parent)
{
    PylonInitialize();
}

CameraManager::~CameraManager()
{
    // Releases all pylon resources.
    qDebug() << "~CameraManager";
    PylonTerminate();
}

int CameraManager::searchCameras()
{
    mCameraList.clear();
    DeviceInfoList_t devices;

    try {
        // Get the GigE transport layer.
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        IGigETransportLayer *pTL = dynamic_cast<IGigETransportLayer*>(tlFactory.CreateTl(BaslerGigEDeviceClass));
        if (pTL == NULL) {
            throw RUNTIME_EXCEPTION("No GigE transport layer available.");
        }

        if (pTL->EnumerateDevices(devices) == 0) {
            throw RUNTIME_EXCEPTION("No GigE cameras present.");
        }

        for (size_t i = 0; i < devices.size(); ++i) {
            string sn = devices[i].GetFriendlyName();
            mCameraList << QString::fromStdString(sn);
            // qDebug() << "Using camera " << i << ": " << devices[i].GetModelName() << " (" << devices[i].GetIpAddress() << ")" << endl;
        }
    } catch (const GenICam::GenericException &e) {
        qCritical() << "An exception occurred: " << e.GetDescription() << endl;
        devices.clear();
    }
    // 本地模拟
    mCameraList << "Camera0" << "Camera1" << "Camera2" << "Camera3" << "Camera5" << "Camera4";
    // 对mCameraList排序
    mCameraList.sort();
    emit sigCameraUpdate(mCameraList);
    mCamerasInfo = devices;

    return mCamerasInfo.size();
}

bool CameraManager::openCamera(QString &cameraFN)
{
    try {
        CDeviceInfo cInfo;
        //        cInfo.SetDeviceClass(BaslerGigEDeviceClass);
        String_t str = String_t(cameraFN.toStdString().c_str());
        cInfo.SetFriendlyName(str);

        CBaslerGigEInstantCamera *camera = new CBaslerGigEInstantCamera;

        camera->Attach(CTlFactory::GetInstance().CreateDevice(cInfo));

        registerHandler(camera);

        bool isOpen = camera->IsOpen();

        if(!isOpen) {
            camera->Open();
            // Add the AutoPacketSizeConfiguration and let pylon delete it when not needed anymore.
            camera->RegisterConfiguration(new CAutoPacketSizeConfiguration(), Pylon::RegistrationMode_Append, Pylon::Cleanup_Delete);
            qDebug() << cameraFN + QString(" Open()");
        } else {
            qInfo() << "Camera already open";
        }

        mCurrentCamera = camera;
        mOpenedCameras.insert(cameraFN, camera);
    } catch (const Pylon::GenericException &e) {
        qCritical() << QString("OpenCamera Error: ") + QString("An exception occurred: ") + QString(e.GetDescription());
        return false;
    }

    return true;
}

void CameraManager::load(QString &cameraFN, QString &fileName)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);

    if (camera == NULL) {
        return;
    }

    CFeaturePersistence::Load(fileName.toUtf8().data(), &camera->GetNodeMap(), true);
}

void CameraManager::save(QString &cameraFN)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);

    if (camera == NULL) {
        return;
    }

    QString path = QDir::currentPath();
    QString fileName = QString("%1/camera/%2.pfs").arg(path).arg(cameraFN);

    CFeaturePersistence::Save(fileName.toUtf8().data(), &camera->GetNodeMap());
}

void CameraManager::closeCamera(QString &cameraFN)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);
    if (camera == NULL) {
        return;
    }

    try {
        if(camera->IsOpen()) {
            if(camera->IsGrabbing()) {
                camera->StopGrabbing();
            }
            camera->Close();

            //            mCurrentCamera->DetachDevice();
        }
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void CameraManager::grabOne(QString &cameraFN)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        // Camera may have been disconnected.
        if (!camera->IsOpen() || camera->IsGrabbing()) {
            return;
        }

        // Since we may switch between single and continuous shot, we must configure the camera accordingly.
        // The predefined configurations are only executed once when the camera is opened.
        // To be able to use them in our use case, we just call them explicitly to apply the configuration.
        mSingleConfiguration.OnOpened(*camera);

        // Grab one image.
        // When the image is received, pylon will call out the OnImageGrab() handler.
        camera->StartGrabbing(1, Pylon::GrabStrategy_OneByOne, Pylon::GrabLoop_ProvidedByInstantCamera);
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void CameraManager::grabContinuous(QString &cameraFN)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);
    if (camera == NULL) {
        return;
    }

    try {
        // Camera may have been disconnected.
        if (!camera->IsOpen() || camera->IsGrabbing()) {
            return;
        }

        // Since we may switch between single and continuous shot, we must configure the camera accordingly.
        // The predefined configurations are only executed once when the camera is opened.
        // To be able to use them in our use case, we just call them explicitly to apply the configuration.
        mContinousConfiguration.OnOpened(*camera);

        // Grab one image.
        // When the image is received, pylon will call out the OnImageGrab() handler.
        camera->StartGrabbing(Pylon::GrabStrategy_LatestImages, Pylon::GrabLoop_ProvidedByInstantCamera);
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void CameraManager::stopGrab(QString &cameraFN)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(cameraFN, NULL);
    if (camera == NULL) {
        return;
    }

    try {
        if(camera->IsGrabbing()) {
            camera->StopGrabbing();
        }
    } catch (Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void CameraManager::setAcquisitionFrameRate(QString &name, double value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();
        const CBooleanPtr frameRate = nodemap.GetNode("AcquisitionFrameRateEnable");
        frameRate->SetValue(TRUE);
        const CFloatPtr frameRateABS = nodemap.GetNode("AcquisitionFrameRateAbs");
        frameRateABS->SetValue(value);
    } catch (const GenICam::GenericException &e) {
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::getAcquisitionFrameRate(QString &name, double &minValue, double &value, double &maxValue, double &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();
        const CFloatPtr frameRateABS = nodemap.GetNode("AcquisitionFrameRateAbs");
        minValue = frameRateABS->GetMin();
        value = frameRateABS->GetValue();
        maxValue = frameRateABS->GetMax();
        inc = 1;
        //inc = frameRateABS->GetInc();
    } catch (const GenICam::GenericException &e) {
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::setExposureTime(QString &name, qint64 time)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try{
        INodeMap& nodemap = camera->GetNodeMap();
        CIntegerPtr exposureTimeRaw(nodemap.GetNode("ExposureTimeRaw"));

        qint64 newExposureRaw = adjust(time, exposureTimeRaw->GetMin(), exposureTimeRaw->GetMax(), exposureTimeRaw->GetInc());
        exposureTimeRaw->SetValue(newExposureRaw);
        qDebug() << "ExposureTime" << exposureTimeRaw->GetValue();
    } catch(const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::getExposureTime(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try{
        INodeMap& nodemap = camera->GetNodeMap();
        CIntegerPtr exposureTimeRaw(nodemap.GetNode("ExposureTimeRaw"));

        minValue = exposureTimeRaw->GetMin();
        value = exposureTimeRaw->GetValue();
        maxValue = exposureTimeRaw->GetMax();
        inc = exposureTimeRaw->GetInc();
    } catch(const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::setGain(QString &name, qint64 value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }
    // Note: Some newer camera models may have auto functions enabled.
    //       To be able to set the gain value to a specific value
    //       the Gain Auto function must be disabled first.
    // Access the enumeration type node GainAuto.
    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CEnumerationPtr gainAuto(nodemap.GetNode("GainAuto"));

        if (IsWritable(gainAuto)){
            gainAuto->FromString("Off");
        }

        // Access the GainRaw integer type node. This node is available for IIDC 1394 and GigE camera devices.
        CIntegerPtr gainRaw(nodemap.GetNode("GainRaw"));
        // Make sure the calculated value is valid.
        qint64 newGainRaw = adjust(value, gainRaw->GetMin(), gainRaw->GetMax(), gainRaw->GetInc());
        gainRaw->SetValue(newGainRaw);
        qDebug() << "Gain : " << gainRaw->GetValue() << " (Min: " << gainRaw->GetMin() << "; Max: " << gainRaw->GetMax() << "; Inc: " << gainRaw->GetInc() << ")";
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::getGain(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }
    // Note: Some newer camera models may have auto functions enabled.
    //       To be able to set the gain value to a specific value
    //       the Gain Auto function must be disabled first.
    // Access the enumeration type node GainAuto.
    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CEnumerationPtr gainAuto(nodemap.GetNode("GainAuto"));

        if (IsWritable(gainAuto)){
            gainAuto->FromString("Off");
        }

        // Access the GainRaw integer type node. This node is available for IIDC 1394 and GigE camera devices.
        CIntegerPtr gainRaw(nodemap.GetNode("GainRaw"));
        // Make sure the calculated value is valid.
        minValue = gainRaw->GetMin();
        value = gainRaw->GetValue();
        maxValue = gainRaw->GetMax();
        inc = gainRaw->GetInc();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::setAOI(QString &name, qint64 width, qint64 height, qint64 offsetX, qint64 offsetY)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    // Set the AOI:
    INodeMap& nodemap = camera->GetNodeMap();

    // Get the integer nodes describing the AOI.
    CIntegerPtr pOffsetX(nodemap.GetNode("OffsetX"));
    CIntegerPtr pOffsetY(nodemap.GetNode("OffsetY"));
    CIntegerPtr pWidth(nodemap.GetNode("Width"));
    CIntegerPtr pHeight(nodemap.GetNode("Height"));

    // On some cameras the offsets are read-only,
    // so we check whether we can write a value. Otherwise, we would get an exception.
    // GenApi has some convenience predicates to check this easily.
    if (IsWritable(pOffsetX)) {
        qint64 newOffsetX = adjust(offsetX, pOffsetX->GetMin(), pOffsetX->GetMax(), pOffsetX->GetInc());
        pOffsetX->SetValue(newOffsetX);
    }

    if (IsWritable(pOffsetY)) {
        qint64 newOffsetY = adjust(offsetY, pOffsetY->GetMin(), pOffsetY->GetMax(), pOffsetY->GetInc());
        pOffsetX->SetValue(newOffsetY);
    }

    // Some properties have restrictions. Use GetInc/GetMin/GetMax to make sure you set a valid value.
    if (IsWritable(pWidth)) {
        qint64 newWidth = adjust(width, pWidth->GetMin(), pWidth->GetMax(), pWidth->GetInc());
        pWidth->SetValue(newWidth);
    }

    if (IsWritable(pHeight)) {
        qint64 newHeight = adjust(height, pHeight->GetMin(), pHeight->GetMax(), pHeight->GetInc());
        pHeight->SetValue(newHeight);
    }

    qDebug() << "offsetX: " << pOffsetX->GetValue();
    qDebug() << "OffsetY: " << pOffsetY->GetValue();

    qDebug() << "Width: " << pWidth->GetValue();
    qDebug() << "Height: " << pHeight->GetValue();
}

void CameraManager::setPixelFormat(QString &name, const QString &format)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }
    // Set the pixel data format.
    INodeMap& nodemap = camera->GetNodeMap();
    CEnumerationPtr PixelFormat(nodemap.GetNode("PixelFormat"));
    PixelFormat->FromString("Mono8");
}

void CameraManager::setWidth(QString &name, qint64 value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pWidth(nodemap.GetNode( "Width"));

        if (IsWritable(pWidth)) {
            qint64 newWidth = adjust(value, pWidth->GetMin(), pWidth->GetMax(), pWidth->GetInc());
            pWidth->SetValue(newWidth);
        }
        qDebug() << "Width: " << pWidth->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::getWidth(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pWidth(nodemap.GetNode( "Width"));

        if (IsReadable(pWidth)) {
            minValue = pWidth->GetMin();
            value = pWidth->GetValue();
            maxValue = pWidth->GetMax();
            inc = pWidth->GetInc();
        }
        qDebug() << "Width: " << pWidth->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::setHeight(QString &name, qint64 value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);
    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pHeight( nodemap.GetNode("Height"));

        if (IsWritable(pHeight)) {
            qint64 newHeight = adjust(value, pHeight->GetMin(), pHeight->GetMax(), pHeight->GetInc());
            pHeight->SetValue(newHeight);
        }
        qDebug() << "Height: " << pHeight->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::getHeight(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);
    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pHeight( nodemap.GetNode("Height"));

        if (IsReadable(pHeight)) {
            minValue = pHeight->GetMin();
            value = pHeight->GetValue();
            maxValue = pHeight->GetMax();
            inc = pHeight->GetInc();
        }
        qDebug() << "Height: " << pHeight->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::setoffsetX(QString &name, qint64 value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pOffsetX( nodemap.GetNode( "OffsetX"));

        if (IsWritable(pOffsetX)) {
            qint64 newOffsetX = adjust(value, pOffsetX->GetMin(), pOffsetX->GetMax(), pOffsetX->GetInc());
            pOffsetX->SetValue(newOffsetX);
        }
        qDebug() << "offsetX: " << pOffsetX->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::getoffsetX(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pOffsetX( nodemap.GetNode( "OffsetX"));

        if (IsReadable(pOffsetX)) {
            minValue = pOffsetX->GetMin();
            value = pOffsetX->GetValue();
            maxValue = pOffsetX->GetMax();
            inc = pOffsetX->GetInc();
        }
        qDebug() << "offsetX: " << pOffsetX->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }

}

void CameraManager::setoffsetY(QString &name, qint64 value)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pOffsetY(nodemap.GetNode( "OffsetY"));

        if (IsWritable(pOffsetY)) {
            qint64 newOffsetX = adjust(value, pOffsetY->GetMin(), pOffsetY->GetMax(), pOffsetY->GetInc());
            pOffsetY->SetValue(newOffsetX);
        }
        qDebug() << "offsetY: " << pOffsetY->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

void CameraManager::getoffsetY(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc)
{
    CBaslerGigEInstantCamera* camera = mOpenedCameras.value(name, NULL);

    if (camera == NULL) {
        return;
    }

    try {
        INodeMap& nodemap = camera->GetNodeMap();

        CIntegerPtr pOffsetY( nodemap.GetNode( "OffsetY"));

        if (IsWritable(pOffsetY)) {
            minValue = pOffsetY->GetMin();
            value = pOffsetY->GetValue();
            maxValue = pOffsetY->GetMax();
            inc = pOffsetY->GetInc();
        }
        qDebug() << "offsetY: " << pOffsetY->GetValue();
    } catch (const GenICam::GenericException &e) {
        // Error handling.
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

bool CameraManager::isOpened(QString &name)
{
    return mOpenedCameras.contains(name);
}

void CameraManager::addOpenCamera(const QString &name, CBaslerGigEInstantCamera *camera)
{
    mOpenedCameras.insert(name, camera);
}

void CameraManager::removeOpenCamera(const QString &name)
{
    mOpenedCameras.remove(name);
}

void CameraManager::OnImagesSkipped(CInstantCamera &camera, size_t countOfSkippedImages)
{

}

void CameraManager::OnImageGrabbed(CInstantCamera &camera, const CGrabResultPtr &grabResult)
{
    // 将结果发送出去
    // 不是主线程
    qDebug() << QString("OnImageGrabbed+");
    qDebug() <<QThread::currentThreadId();
    // Also, you shouldn't access any UI objects, since we are not in the GUI thread.
    // We just store the grab result in the document and post a message to the CFrameWnd
    // to notify it of the new result. In response to this message, we will update the GUI.

    // The following line is commented out as this function will be called very often
    // filling up the debug output.

    // The m_ptrGrabResult will be accessed from different threads,
    // so we need to protect it with the mutex.
    QMutexLocker locker(&mutex);

    // When overwriting the current CGrabResultPtr, the old result will automatically be
    // released and reused by CInstantCamera.
    CImageFormatConverter fc;
    //     CPylonImage image;
    //     camera.RetrieveResult(2000, grabResult, TimeoutHandling_Return);
    if (grabResult->GrabSucceeded()) {
        //         emit addTrace(QString("Snap, image %1").arg(grabResult->GetWidth()) + QString("x%1 [px]").arg(grabResult->GetHeight()));
        CPylonImage mImage;
        fc.OutputPixelFormat = PixelType_RGB8packed;
        fc.Convert(mImage, grabResult);
        cv::Mat image(mImage.GetHeight(), mImage.GetWidth(), CV_8UC3, (uint8_t*)mImage.GetBuffer());
        //         sigupdateImage(image);
        //         QImage *qtImage = new QImage((uint8_t*)image.GetBuffer(), grabResult->GetWidth(), grabResult->GetHeight(),QImage::Format_RGB888);
        //         QImage qtImage((uint8_t*)mImage.GetBuffer(), grabResult->GetWidth(), grabResult->GetHeight(),QImage::Format_RGB888);

        //         emit sigCurrentImage(qtImage);
    } else {
        qWarning() << QString("An exception occurred: ") << grabResult->GetErrorDescription();
        //         addTrace(QString("An exception occurred: ") + QString(grabResult->GetErrorDescription()), QColor("red"));
    }
}

void CameraManager::OnAttach(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnAttach";

}

void CameraManager::OnAttached(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnAttached";
}

void CameraManager::OnDetach(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnDetach";
}

void CameraManager::OnDetached(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnDetached";
}

void CameraManager::OnDestroy(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnDestroy";
}

void CameraManager::OnDestroyed(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnDestroyed";
}

void CameraManager::OnOpen(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnOpen+";
    qDebug() << QThread::currentThreadId();
    Pylon::String_t strFriendlyName = camera.GetDeviceInfo().GetFriendlyName();
    qDebug() <<  strFriendlyName;
}

void CameraManager::OnOpened(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnOpened+";
    qDebug() << QThread::currentThreadId();
}

void CameraManager::OnClose(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnClose";
}

void CameraManager::OnClosed(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnClosed";
    mOpenedCameras.remove(QString(camera.GetDeviceInfo().GetFriendlyName()));
}

void CameraManager::OnGrabStart(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnGrabStart + ";
    qDebug() << QThread::currentThreadId();
    // Reset statistics.
    //    mCntGrabbedImages = 0;
    //    mCntSkippedImages = 0;
    //    mCntGrabErrors = 0;
}

void CameraManager::OnGrabStarted(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnGrabStarted + ";
    qDebug() << QThread::currentThreadId();
}

void CameraManager::OnGrabStop(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnGrabStop + ";
    qDebug() << QThread::currentThreadId();
}

void CameraManager::OnGrabStopped(CInstantCamera &camera)
{
    Q_UNUSED(camera);
    qDebug() << "OnGrabStopped + ";
    qDebug() << QThread::currentThreadId();
    // Deregister all configurations.
    camera.DeregisterConfiguration(&mSingleConfiguration);
    camera.DeregisterConfiguration(&mContinousConfiguration);
}

void CameraManager::OnGrabError(CInstantCamera &camera, const char *errorMessage)
{
    Q_UNUSED(camera);
    Q_UNUSED(errorMessage);
    qDebug() << "OnGrabError";
}

void CameraManager::OnCameraDeviceRemoved(CInstantCamera &camera)
{
    // This method is called from a different thread when the camera device removal has been detected.
    qDebug() << "OnCameraDeviceRemoved";
    mOpenedCameras.remove(QString(camera.GetDeviceInfo().GetFriendlyName()));
    try {
        // Mark everything as invalid.
        QMutexLocker locker(&mutex);
        mGrabResult.Release();
        //        m_bitmapImage.Release();
        camera.DestroyDevice();
    } catch (const Pylon::GenericException e) {
        qDebug() << "An exception occurred: " << e.GetDescription();
    }
}

bool CameraManager::registerHandler(CInstantCamera *camera)
{
    try {
        // Register this object as an image event handler, so we will be notified of new new images
        // See Pylon::CImageEventHandler for details
        camera->RegisterImageEventHandler(this, Pylon::RegistrationMode_ReplaceAll, Pylon::Ownership_ExternalOwnership);
        // Register this object as a configuration event handler, so we will be notified of camera state changes.
        // See Pylon::CConfigurationEventHandler for details
        camera->RegisterConfiguration(this, Pylon::RegistrationMode_ReplaceAll, Pylon::Ownership_ExternalOwnership);
    } catch (const Pylon::GenericException& e) {
        qDebug() << QString(e.what());
        return false;
    }
    return true;
}

qint64 CameraManager::adjust(qint64 val, qint64 minimum, qint64 maximum, qint64 inc)
{
    // Check the input parameters.
    if (inc <= 0) {
        // Negative increments are invalid.
        throw LOGICAL_ERROR_EXCEPTION("Unexpected increment %d", inc);
    }
    if (minimum > maximum) {
        // Minimum must not be bigger than or equal to the maximum.
        throw LOGICAL_ERROR_EXCEPTION("minimum bigger than maximum.");
    }

    // Check the lower bound.
    if (val < minimum) {
        return minimum;
    }

    // Check the upper bound.
    if (val > maximum) {
        return maximum;
    }

    // Check the increment.
    if (inc == 1) {
        // Special case: all values are valid.
        return val;
    } else {
        // The value must be min + (n * inc).
        // Due to the integer division, the value will be rounded down.
        return minimum + ( ((val - minimum) / inc) * inc );
    }
}
