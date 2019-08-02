#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QMdiArea>
#include "cameramanager.h"
#include "devicesdock.h"
#include "paramdock.h"
#include "camera/cameraform.h"

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = 0);
    ~CameraWindow();
private slots:
    /**
     * @brief 初始化，更新菜单栏
     */
    void updateMenus();

    /**
     * @brief 保存图片
     */
    void saveImage();

    /**
     * @brief 打开相机
     */
    void openCamera();

    /**
     * @brief 关闭相机
     */
    void closeCamera();

    /**
     * @brief 采集一张图片
     */
    void grabOne();

    /**
     * @brief 连续采集图片
     */
    void grabContinous();

    /**
     * @brief 停止采集图片
     */
    void grabStop();
    
    /**
     * @brief 缩小视图
     */
    void zoomIn();
    
    /**
     * @brief 放大视图
     */
    void zoomOut();

    /**
     * @brief 自适应
     */
    void zoomFit();

    /**
     * @brief 显示网格
     * @param checked
     */
    void showGrid(bool checked = false);
    
    void updateCurrentCamera(QString &cameraName);

    void handleImageInfo(QPoint point, QRgb rgb);
private:
    void createActionConnections();

    void createDocks();

    /**
     * @brief 寻找对应的子窗口是否已经打开了
     * @param 相机名称
     * @return
     */
    QMdiSubWindow *findMdiChild(const QString &cameraName) const;

    /**
     * @brief 当前活跃的子窗口
     * @return
     */
    CameraForm *activeMdiChild() const;
private:
    Ui::CameraWindow *ui;

    QString mCurrentCamera;
    // 设备列表
    QDockWidget *mCameraListWidget;
    // 设备列表的界面
    DevicesDock* mDevicesDock;
    // 相机属性
    QDockWidget *mCameraParamsWidget;
    // 相机属性的界面
    ParamDock* mParamDock;
};

#endif // CAMERAWINDOW_H
