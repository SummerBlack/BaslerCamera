#pragma execution_character_set("utf-8")

#include "cameraform.h"
#include "ui_cameraform.h"
#include <QDebug>
#include <QFileDialog>

CameraForm::CameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraForm),
    mScene(new CameraScene),
    mView(new QGraphicsView(mScene)),
    mCamera(new MyCamera)
{
    ui->setupUi(this);
    initMenu();

    ui->widget->layout()->addWidget(mView);
    // 状态栏显示鼠标的坐标和所在像素的颜色
    connect(mScene, &CameraScene::sigImageInfo, this, &CameraForm::sigImageInfo);
    // 相机采集和显示
    connect(mCamera, &MyCamera::sigGrabNewImage, this, &CameraForm::updateCameraImage);
}

CameraForm::~CameraForm()
{
    delete ui;
    delete mMenu;
    delete mView;
    delete mScene;

    closeCamera();
}

void CameraForm::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    //在鼠标点击的位置显示鼠标右键菜单
    mMenu->exec(QCursor::pos());
}

void CameraForm::setCameraId(int id)
{
    mCameraId = id;
    ui->btn_Number->setText(QString::number(id));
}

void CameraForm::updateCameraImage(cv::Mat image)
{
//    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_Indexed8);
    mScene->updateImage(img);
}

void CameraForm::updateROI(cv::Mat image, double width, double height, double x, double y)
{
//    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_Indexed8);
    mScene->updateImage(img);
    mScene->updateRect(QRectF(0, 0, width, height), QPointF(x, y));
}

void CameraForm::zoomIn()
{
    changeSceneScale(mScale*1.2);
}

void CameraForm::zoomOut()
{
    changeSceneScale(mScale*0.83);
}

void CameraForm::fit()
{
    mView->fitInView(mScene->sceneRect(), Qt::KeepAspectRatio);
    QMatrix matrix = mView->matrix();
    mScale = matrix.m11();
}

void CameraForm::resetScale()
{
    changeSceneScale(1);
}

void CameraForm::changeSceneScale(const double &scale)
{
    mScale = scale;
    QMatrix matrix;
    matrix.scale(scale, scale);

    mView->setMatrix(matrix);
}

void CameraForm::showCamera()
{
    qDebug() << "showCamera";
    //    updateCameraImage(QImage(QString("D:\\TestResult\\201811\\0\\1.bmp")));
    mScene->showCameraOnly();
}

void CameraForm::saveImage()
{
    QImage image;
    bool res = mScene->getImage(image);
    if (res) {
        QString filePath = QFileDialog::getSaveFileName(this, "Save As", "", tr("Images (*.bmp *.png *.jpg)"));
        image.save(filePath);
    }
}


void CameraForm::showGrid(bool checked)
{
    mScene->showGrid(checked, mScale);
}

void CameraForm::initMenu()
{
    // 初始化右击菜单
    mMenu = new QMenu(this);
    QAction* camera = new QAction(QIcon(""), tr("显示图像"), mMenu);

    QAction* saveImage = new QAction(QIcon(""), tr("保存图片"), mMenu);

    QAction* showGrid = new QAction(QIcon(""), tr("显示网格"), mMenu);
    showGrid->setCheckable(true);

    QAction* zoomIn = new QAction(QIcon(""), tr("放大"), mMenu);
    QAction* zoomOut = new QAction(QIcon(""), tr("缩小"), mMenu);
    QAction* fit = new QAction(QIcon(""), tr("自适应"), mMenu);
    QAction* reset = new QAction(QIcon(""), tr("原大小"), mMenu);

    mMenu->addAction(camera);

    mMenu->addSeparator();

    mMenu->addAction(saveImage);
    mMenu->addSeparator();

    mMenu->addAction(zoomIn);
    mMenu->addAction(zoomOut);
    mMenu->addAction(fit);
    mMenu->addAction(reset);
    mMenu->addSeparator();

    mMenu->addAction(showGrid);

    connect(camera, &QAction::triggered, this, &CameraForm::showCamera);

    connect(saveImage, &QAction::triggered, this, &CameraForm::saveImage);

    connect(zoomIn, &QAction::triggered, this, &CameraForm::zoomIn);
    connect(zoomOut, &QAction::triggered, this, &CameraForm::zoomOut);
    connect(fit, &QAction::triggered, this, &CameraForm::fit);
    connect(reset, &QAction::triggered, this, &CameraForm::resetScale);
    connect(showGrid, &QAction::triggered, this, &CameraForm::showGrid);

}

void CameraForm::updateSTValue(double sValue, int sFreq, double tValue, int tFreq)
{
    ui->tbs_Info->setHtml(QApplication::translate("CameraView", QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                                        "p, li { white-space: pre-wrap; }\n"
                                                                        "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
                                                                        "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#aa0000;\">S:%1</span> <span style=\" color:#ffffff;\">/ %2</span> <span style=\" font-size:12pt; font-weight:600; color:#aa0000;\"> T:%3</span> <span style=\" color:#ffffff;\">/ %4</span></p></body></html>")
                                                  .arg(QString::number(sValue, 'g', 3)).arg(sFreq).arg(QString::number(tValue, 'g', 3)).arg(tFreq).toUtf8(), nullptr));

}

QString CameraForm::cameraName() const
{
    return mCameraName;
}

void CameraForm::setCameraName(const QString &cameraName)
{
    mCameraName = cameraName;
    setWindowTitle(cameraName);
}

bool CameraForm::openCamera(const QString &cameraName)
{
    return mCamera->openCamera(cameraName);
}

void CameraForm::closeCamera()
{
    mCamera->closeCamera();
}

void CameraForm::grabOneImage()
{
    mCamera->grabOneImage();
}

void CameraForm::grabContinous()
{
    mCamera->grabContinous();
}

void CameraForm::grabStop()
{
    mCamera->grabStop();
}
