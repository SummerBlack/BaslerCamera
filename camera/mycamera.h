#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include "baslerSDK/include/HardwareTriggerConfiguration.h"

// Settings to use Basler GigE cameras.
using namespace Basler_GigECameraParams;
// Namespace for using pylon objects.
using namespace Pylon;
// Namespace for using cout.
using namespace std;

using namespace GenApi;

class CameraManager;

class MyCamera : public QObject,
        public Pylon::CImageEventHandler             // Allows you to get informed about received images and grab errors.
{
    Q_OBJECT
public:
    explicit MyCamera(QObject *parent = nullptr);
    ~MyCamera();

    /**
     * @brief 打开相机
     * @param cameraFN
     * @return
     */
    bool openCamera(const QString &cameraFN);

    /**
     * @brief 关闭相机
     */
    void closeCamera();

    /**
     * @brief 采集到图像的异步回调
     * @param camera
     * @param grabResult
     */
    void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& grabResult) override;

public slots:
    /**
     * @brief 采集一张图片
     * @param position
     */
    void grabOneImage();
    /**
     * @brief 连续拍照，用于前期调整相机位置
     */
    void grabContinous();

    /**
     * @brief 停止采集图片
     */
    void grabStop();
signals:
    /**
     * @brief 获取到新的图像
     * @param image 图像
     * @param position 拍摄该图像位置
     */
    void sigGrabNewImage(cv::Mat image);
private:
    // 单张拍摄
    CAcquireSingleFrameConfiguration mSingleConfiguration;
    // 连续拍摄
    CAcquireContinuousConfiguration mContinousConfiguration;
    // 硬件触发
    CHardwareTriggerConfiguration mHardwareTriggerConfig;
    // 当前操作的相机
    CBaslerGigEInstantCamera *mCamera = NULL;
    // 相机的名称
    QString mCameraName;
    // 管理所有相机
    CameraManager *mCameraManager;
};

#endif // MYCAMERA_H
