#pragma execution_character_set("utf-8")

#include "camerawindow.h"
#include "ui_camerawindow.h"
#include <QMdiSubWindow>
#include <QDebug>
#include <QMessageBox>

CameraWindow::CameraWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
    // 子窗口切换时，要更新菜单栏
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &CameraWindow::updateMenus);
    createDocks();
    createActionConnections();

    updateMenus();
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::updateMenus()
{
     qDebug() << "updateMenus";
     bool hasMdiChild = (activeMdiChild() != 0);
     ui->action_Save->setEnabled(hasMdiChild);
     ui->action_ZoomIn->setEnabled(hasMdiChild);
     ui->action_ZoomOut->setEnabled(hasMdiChild);
     ui->action_ZoomFit->setEnabled(hasMdiChild);
     ui->action_ShowGrid->setEnabled(hasMdiChild);

     ui->action_tile->setEnabled(hasMdiChild);
     ui->action_cascade->setEnabled(hasMdiChild);
}

void CameraWindow::saveImage()
{
    CameraForm *mdiChild = activeMdiChild();
    mdiChild->saveImage();
}

void CameraWindow::openCamera()
{
    // 打开相机
    CameraForm* child = new CameraForm;
    child->setCameraName(mCurrentCamera);
    bool res = child->openCamera(mCurrentCamera);

    if (res) {
        ui->mdiArea->addSubWindow(child)->showMaximized();
        connect(child, &CameraForm::sigImageInfo, this, &CameraWindow::handleImageInfo);
        ui->action_Open->setEnabled(false);
        ui->action_Close->setEnabled(true);
        ui->action_Single->setEnabled(true);
        ui->action_Contious->setEnabled(true);
        ui->action_Stop->setEnabled(true);

        mParamDock->updateCamera(mCurrentCamera);
    } else {
        delete child;
        QMessageBox::information(this, "提示", "打开失败");
    }
}

void CameraWindow::closeCamera()
{
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // 当前的窗口相机去采集图像
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        disconnect(mdiChild, &CameraForm::sigImageInfo, this, &CameraWindow::handleImageInfo);
        mdiChild->closeCamera();
        ui->mdiArea->removeSubWindow(mdiChild);
        mdiChild->close();

        ui->action_Open->setEnabled(true);
        ui->action_Close->setEnabled(false);
        ui->action_Single->setEnabled(false);
        ui->action_Contious->setEnabled(false);
        ui->action_Stop->setEnabled(false);
        mParamDock->updateCamera(mCurrentCamera);
    }
}

void CameraWindow::grabOne()
{
    // 加载显示界面
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // 当前的窗口相机去采集图像
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabOneImage();
    }
}

void CameraWindow::grabContinous()
{
    // 加载显示界面
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // 当前的窗口相机去采集图像
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabContinous();
    }
}

void CameraWindow::grabStop()
{
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // 当前的窗口相机去采集图像
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabStop();
    }
}

void CameraWindow::zoomIn()
{
    CameraForm* form = activeMdiChild();
    if (form != NULL) {
        form->zoomIn();
    }
}

void CameraWindow::zoomOut()
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->zoomOut();
    }
}

void CameraWindow::zoomFit()
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->fit();
    }
}

void CameraWindow::showGrid(bool checked)
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->showGrid(checked);
    }
}

void CameraWindow::updateCurrentCamera(QString &cameraName)
{
    mCurrentCamera = cameraName;

    if (findMdiChild(mCurrentCamera)) {
        ui->action_Open->setEnabled(false);
        ui->action_Close->setEnabled(true);
        ui->action_Single->setEnabled(true);
        ui->action_Contious->setEnabled(true);
        ui->action_Stop->setEnabled(true);
    } else {
        ui->action_Open->setEnabled(true);
        ui->action_Close->setEnabled(false);
        ui->action_Single->setEnabled(false);
        ui->action_Contious->setEnabled(false);
        ui->action_Stop->setEnabled(false);
    }
}

void CameraWindow::handleImageInfo(QPoint point, QRgb rgb)
{
    if (point.x() == -1 || point.y() == -1) {
        // 鼠标移出窗口
        ui->statusbar->showMessage("");
    } else {
        // 鼠标在窗口中的位置
        ui->statusbar->showMessage(QString("(%1, %2)  (R:%3, G:%4, B:%5)")
                                   .arg(point.x())
                                   .arg(point.y())
                                   .arg(qRed(rgb))
                                   .arg(qGreen(rgb))
                                   .arg(qBlue(rgb)));
    }

}

void CameraWindow::createActionConnections()
{
    connect(ui->action_Save, &QAction::triggered, this, &CameraWindow::saveImage);

    connect(ui->action_Exit, &QAction::triggered, this, &CameraWindow::close);

    connect(ui->action_Open, &QAction::triggered, this, &CameraWindow::openCamera);

    connect(ui->action_Close, &QAction::triggered, this, &CameraWindow::closeCamera);

    connect(ui->action_Single, &QAction::triggered, this, &CameraWindow::grabOne);

    connect(ui->action_Contious, &QAction::triggered, this, &CameraWindow::grabContinous);

    connect(ui->action_Stop, &QAction::triggered, this, &CameraWindow::grabStop);

    connect(ui->action_ZoomIn, &QAction::triggered, this, &CameraWindow::zoomIn);

    connect(ui->action_ZoomOut, &QAction::triggered, this, &CameraWindow::zoomOut);

    connect(ui->action_ZoomFit, &QAction::triggered, this, &CameraWindow::zoomFit);

    ui->action_ShowGrid->setCheckable(true);
    connect(ui->action_ShowGrid, &QAction::triggered, this, &CameraWindow::showGrid);

    ui->action_Open->setEnabled(false);
    ui->action_Close->setEnabled(false);
    ui->action_Single->setEnabled(false);
    ui->action_Contious->setEnabled(false);
    ui->action_Stop->setEnabled(false);

    connect(ui->action_Device, &QAction::triggered, [this](bool checked){
        if (checked) {
            mCameraListWidget->show();
        } else {mCameraListWidget->hide();}});
    connect(ui->action_Params, &QAction::triggered, [this](bool checked){
        if (checked) {
            mCameraParamsWidget->show();
        } else {mCameraParamsWidget->hide();}});

    connect(ui->action_tile, &QAction::triggered, ui->mdiArea, &QMdiArea::tileSubWindows);
    connect(ui->action_cascade, &QAction::triggered, ui->mdiArea, &QMdiArea::cascadeSubWindows);
}

void CameraWindow::createDocks()
{
    // 设备列表
    mCameraListWidget = new QDockWidget(this);
    mCameraListWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    mDevicesDock = new DevicesDock;
    mCameraListWidget->setWidget(mDevicesDock);
    mCameraListWidget->setWindowTitle("设备");
    addDockWidget(Qt::LeftDockWidgetArea, mCameraListWidget);
//    mCameraListWidget->setVisible(false);
    // 当前点击的是哪个相机
    connect(mDevicesDock, &DevicesDock::sigActivated, this, &CameraWindow::updateCurrentCamera);
    // 参数列表
    mCameraParamsWidget = new QDockWidget(this);
    mCameraParamsWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    mParamDock = new ParamDock;
    mCameraParamsWidget->setWidget(mParamDock);
    mCameraParamsWidget->setWindowTitle("参数");
    addDockWidget(Qt::LeftDockWidgetArea, mCameraParamsWidget);
//    mCameraParamsWidget->setVisible(false);
    connect(mDevicesDock, &DevicesDock::sigActivated, mParamDock, &ParamDock::updateCamera);
}

QMdiSubWindow *CameraWindow::findMdiChild(const QString &cameraName) const
{
    qDebug() << ui->mdiArea->subWindowList().size();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        CameraForm *mdiChild = qobject_cast<CameraForm *>(window->widget());
        if (mdiChild != NULL && mdiChild->cameraName() == cameraName)
            return window;
    }
    return 0;
}

CameraForm *CameraWindow::activeMdiChild() const
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<CameraForm *>(activeSubWindow->widget());
    return 0;
}
