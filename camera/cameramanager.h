#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <QMap>
#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include "opencv2/opencv.hpp"

// Settings to use Basler GigE cameras.
using namespace Basler_GigECameraParams;
// Namespace for using pylon objects.
using namespace Pylon;
// Namespace for using cout.
using namespace std;

using namespace GenApi;


class CameraManager : public QObject,
        public Pylon::CImageEventHandler,             // Allows you to get informed about received images and grab errors.
        public Pylon::CConfigurationEventHandler     // Allows you to get informed about device removal.
{
    Q_OBJECT
private:
    static CameraManager *mInstance;
    explicit CameraManager(QObject *parent = nullptr);

public:
    static CameraManager *getInstance(){
        return mInstance;
    }

    ~CameraManager();
public:
    /**
     * @brief 搜索连接的所有相机
     * @return
     */
    int searchCameras();

    /**
     * @brief 打开对应的Camera
     * @param camera的FriendlyName
     * @return 错误码 0:成功 -1：失败
     */
    bool openCamera(QString &cameraFN);

    /**
     * @brief 加载配置文件
     * @param cameraFN
     * @param fileName
     */
    void load(QString &cameraFN, QString &fileName);

    /**
     * @brief 保存配置文件
     * @param cameraFN
     */
    void save(QString &cameraFN);

    /**
     * @brief 关闭Camera
     * @param cameraFN
     */
    void closeCamera(QString &cameraFN);

    /**
     * @brief 一次采集一张图片
     */
    void grabOne(QString &cameraFN);

    /**
     * @brief 连续采集图片
     */
    void grabContinuous(QString &cameraFN);

    /**
     * @brief 停止采集图像
     * @param cameraFN
     */
    void stopGrab(QString &cameraFN);

    /**
     * @brief 设置帧率
     * @param name
     * @param value
     */
    void setAcquisitionFrameRate(QString &name, double value);

    /**
     * @brief 获取帧率
     * @param name
     * @param minValue
     * @param value
     * @param maxValue
     * @param inc
     */
    void getAcquisitionFrameRate(QString &name, double &minValue, double &value, double &maxValue, double &inc);

    /**
     * @brief 设置曝光时间
     * @param time
     */
    void setExposureTime(QString &name, qint64 time);

    /**
     * @brief 获取曝光时间
     * @param name
     * @param minValue
     * @param value
     * @param maxValue
     * @param inc
     */
    void getExposureTime(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    /**
     * @brief 设置增益
     * @param value
     */
    void setGain(QString &name, qint64 value);

    void getGain(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setAOI(QString &name, qint64 width, qint64 height, qint64 offsetX, qint64 offsetY);

    void setPixelFormat(QString &name, const QString &format = QString());

    void setWidth(QString &name, qint64 value);

    void getWidth(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setHeight(QString &name, qint64 value);

    void getHeight(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setoffsetX(QString &name, qint64 value);

    void getoffsetX(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setoffsetY(QString &name, qint64 value);

    void getoffsetY(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    bool isOpened(QString &name);

    void addOpenCamera(const QString& name, CBaslerGigEInstantCamera* camera);

    void removeOpenCamera(const QString& name);

    // Pylon::CImageEventHandler functions
    virtual void OnImagesSkipped(Pylon::CInstantCamera& camera, size_t countOfSkippedImages) override;
    virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& grabResult) override;

    // Pylon::CConfigurationEventHandler functions
    virtual void OnAttach(Pylon::CInstantCamera& camera) override;
    virtual void OnAttached(Pylon::CInstantCamera& camera) override;
    virtual void OnDetach(Pylon::CInstantCamera& camera) override;
    virtual void OnDetached(Pylon::CInstantCamera& camera) override;
    virtual void OnDestroy(Pylon::CInstantCamera& camera) override;
    virtual void OnDestroyed(Pylon::CInstantCamera& camera) override;
    virtual void OnOpen(Pylon::CInstantCamera& camera) override;
    virtual void OnOpened(Pylon::CInstantCamera& camera) override;
    virtual void OnClose(Pylon::CInstantCamera& camera) override;
    virtual void OnClosed(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStart(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStarted(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStop(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStopped(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabError(Pylon::CInstantCamera& camera, const char* errorMessage) override;
    virtual void OnCameraDeviceRemoved(Pylon::CInstantCamera& camera) override;

signals:
    void sigCameraUpdate(const QStringList &list);

    void sigupdateImage(cv::Mat image);

public slots:


private:
    bool registerHandler(CInstantCamera *camera);
    /**
     * @brief Adjust value to make it comply with range and increment passed
     * @param val
     * @param minimum
     * @param maximum
     * @param inc
     * @return
     */
    qint64 adjust(qint64 val, qint64 minimum, qint64 maximum, qint64 inc);

private:
    // 最多连接多少个相机
    const static int mMaxCamerasToUse = 17;

    QMutex mutex;

    // The grab result retrieved from the camera
    CGrabResultPtr mGrabResult;
    // 单张拍摄
    CAcquireSingleFrameConfiguration mSingleConfiguration;
    // 连续拍摄
    CAcquireContinuousConfiguration mContinousConfiguration;
    // 软件触发
    CSoftwareTriggerConfiguration mSoftwareTriggerConfig;

    // 所有的以太网连接的相机
//    CBaslerGigEInstantCameraArray mGigECameras;
    // 当前操作的相机
    CBaslerGigEInstantCamera *mCurrentCamera = NULL;
    // 搜索到的相机列表
    // List of all attached devices
    Pylon::DeviceInfoList_t mCamerasInfo;
    QStringList mCameraList;
    // 打开的相机缓存
    QMap<QString, CBaslerGigEInstantCamera*> mOpenedCameras;
};

#endif // CAMERAMANAGER_H
