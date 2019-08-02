#ifndef CAMERAFORM_H
#define CAMERAFORM_H

#include <QWidget>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMenu>
#include "opencv2/opencv.hpp"
#include "camera/camerascene.h"
#include "mycamera.h"

namespace Ui {
class CameraForm;
}

class CameraForm : public QWidget
{
    Q_OBJECT

public:
    explicit CameraForm(QWidget *parent = 0);
    ~CameraForm();

    void contextMenuEvent(QContextMenuEvent *event) override;

    /**
     * @brief 设置该视图对应相机的ID
     * @param id
     */
    void setCameraId(int id);

    /**
     * @brief 相机的名称
     * @return
     */
    QString cameraName() const;

    void setCameraName(const QString &cameraName);

    /**
     * @brief 打开相机
     * @param cameraName
     * @return
     */
    bool openCamera(const QString &cameraName);

    /**
     * @brief 关闭相机
     */
    void closeCamera();

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

public slots:
    /**
     * @brief 更新显示相机采集的图像
     * @param image
     */
    void updateCameraImage(cv::Mat image);

    /**
     * @brief 更新视图和对应的矩形框
     * @param image 图像
     * @param width 矩形宽度
     * @param height 矩形高度
     * @param x 矩形左上角
     * @param y 矩形右上角
     */
    void updateROI(cv::Mat image, double width, double height, double x, double y);

    /**
     * @brief 放大
     */
    void zoomIn();

    /**
     * @brief 缩小
     */
    void zoomOut();

    /**
     * @brief 适应视图大小
     */
    void fit();

    /**
     * @brief 还原视图大小
     */
    void resetScale();

    /**
     * @brief 视图的缩放
     * @param scale
     */
    void changeSceneScale(const double &scale);

    /***右击菜单栏的功能*****/
    void showCamera();

    void saveImage();

    void showGrid(bool checked = false);
    /***右击菜单栏的功能*****/
signals:
    void sigImageInfo(QPoint point, QRgb rgb);
private:
    void initMenu();
    /**
     * @brief 更新底部的显示
     * @param sValue
     * @param sFreq
     * @param tValue
     * @param tFreq
     */
    void updateSTValue(double sValue, int sFreq, double tValue, int tFreq);

private:
    Ui::CameraForm *ui;
    QMenu *mMenu = NULL;
    CameraScene *mScene = NULL;
    QGraphicsView *mView = NULL;

    int mCameraId = 0;
    QString mCameraName;

    // 相机(打开/关闭/单拍/连拍/暂停)
    MyCamera *mCamera;

    // 缩放尺度
    double mScale = 1;
};

#endif // CAMERAFORM_H
