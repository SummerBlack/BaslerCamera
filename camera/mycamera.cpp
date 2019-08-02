#include "mycamera.h"
#include "baslerSDK/include/AutoPacketSizeConfiguration.h"
#include <QDebug>
#include "cameramanager.h"

MyCamera::MyCamera(QObject *parent) : QObject(parent),
    mCameraManager(CameraManager::getInstance())
{

}

MyCamera::~MyCamera()
{
    closeCamera();

    delete mCamera;
}

bool MyCamera::openCamera(const QString &cameraFN)
{
    try {
        mCameraName = cameraFN;
        CDeviceInfo cInfo;
//        cInfo.SetDeviceClass(BaslerGigEDeviceClass);
        String_t str = String_t(cameraFN.toStdString().c_str());
        cInfo.SetFriendlyName(str);

        CBaslerGigEInstantCamera *camera = new CBaslerGigEInstantCamera;

        camera->Attach(CTlFactory::GetInstance().CreateDevice(cInfo));

//        registerHandler(camera);
        camera->RegisterImageEventHandler(this, Pylon::RegistrationMode_ReplaceAll, Pylon::Ownership_ExternalOwnership);
        bool isOpen = camera->IsOpen();

        if(!isOpen) {
            camera->Open();
            // Add the AutoPacketSizeConfiguration and let pylon delete it when not needed anymore.
            camera->RegisterConfiguration(new CAutoPacketSizeConfiguration(), Pylon::RegistrationMode_Append, Pylon::Cleanup_Delete);
            qDebug() << cameraFN + QString(" Open()");
        } else {
            qInfo() << "Camera already open";
        }

        mCamera = camera;
        // 添加到管理器中
        mCameraManager->addOpenCamera(cameraFN, camera);
    } catch (const Pylon::GenericException &e) {
        qCritical() << QString("OpenCamera Error: ") + QString("An exception occurred: ") + QString(e.GetDescription());
        mCamera = NULL;
        return false;
    }

    return true;
}

void MyCamera::closeCamera()
{
    if (mCamera == NULL) {
        return;
    }

    try {
        if(mCamera->IsOpen()) {
            if(mCamera->IsGrabbing()) {
                mCamera->StopGrabbing();
            }
            mCamera->DeregisterImageEventHandler(this);
            mCamera->Close();

            mCamera->DetachDevice();
            // 从管理器中删除
            mCameraManager->removeOpenCamera(mCameraName);
        }
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void MyCamera::OnImageGrabbed(CInstantCamera &camera, const CGrabResultPtr &grabResult)
{
    Q_UNUSED(camera);
   // When overwriting the current CGrabResultPtr, the old result will automatically be
   // released and reused by CInstantCamera.
//    CImageFormatConverter fc;
    if (grabResult->GrabSucceeded()) {
        uint32_t width = grabResult->GetWidth();
        uint32_t height = grabResult->GetHeight();
        cv::Mat image(height, width, CV_8UC1, (uint8_t*)(grabResult->GetBuffer()));
        if (!image.empty()) {
            //cv::imwrite("C:\\Users\\CF\\Desktop\\save\\2.jpg", image);
            // 调试发现，如果不clone的话，会导致后续错误，可能是共用了BUFFER问题
            emit sigGrabNewImage(image.clone());
        }
        // 本地模拟
//        int position = qrand() % 6;
//        QString file = QString("D:\\TestResult\\0\\%1.bmp").arg(position);
//        cv::Mat image = cv::imread(cv::String(file.toUtf8().data()));
//        emit sigGrabNewImage(image);
//        qDebug() << position;
    } else {
        qWarning() << QString("An exception occurred: ") << grabResult->GetErrorDescription();
    }
}

void MyCamera::grabOneImage()
{
    if (mCamera == NULL) {
        return;
    }

    try {
        // Camera may have been disconnected.
        if (!mCamera->IsOpen() || mCamera->IsGrabbing()) {
            return;
        }

        // Since we may switch between single and continuous shot, we must configure the camera accordingly.
        // The predefined configurations are only executed once when the camera is opened.
        // To be able to use them in our use case, we just call them explicitly to apply the configuration.
        mSingleConfiguration.OnOpened(*mCamera);

        // Grab one image.
        // When the image is received, pylon will call out the OnImageGrab() handler.
        mCamera->StartGrabbing(1, Pylon::GrabStrategy_OneByOne, Pylon::GrabLoop_ProvidedByInstantCamera);
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void MyCamera::grabContinous()
{
    if (mCamera == NULL) {
        return;
    }

    try {
        // Camera may have been disconnected.
        if (!mCamera->IsOpen() || mCamera->IsGrabbing()) {
            return;
        }

        // Since we may switch between single and continuous shot, we must configure the camera accordingly.
        // The predefined configurations are only executed once when the camera is opened.
        // To be able to use them in our use case, we just call them explicitly to apply the configuration.
        // 软件触发
        mContinousConfiguration.OnOpened(*mCamera);
        // 硬件触发
//        mHardwareTriggerConfig.OnOpened(*mCamera);

        // Grab one image.
        // When the image is received, pylon will call out the OnImageGrab() handler.
        mCamera->StartGrabbing(Pylon::GrabStrategy_LatestImages, Pylon::GrabLoop_ProvidedByInstantCamera);
    } catch(Pylon::GenericException &e) {
        qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}

void MyCamera::grabStop()
{
    if (mCamera == NULL) {
        return;
    }

    try {
        if(mCamera->IsGrabbing()) {
            mCamera->StopGrabbing();
        }
    } catch (Pylon::GenericException &e) {
       qDebug() << QString("An exception occurred: ") + QString(e.GetDescription());
    }
}
