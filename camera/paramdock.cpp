#pragma execution_character_set("utf-8")
#include "paramdock.h"
#include "ui_paramdock.h"
#include <QSettings>
#include <QDir>
#include <QDebug>

ParamDock::ParamDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamDock),
    mCameras(CameraManager::getInstance())
{
    ui->setupUi(this);
}

ParamDock::~ParamDock()
{
    delete ui;
}

void ParamDock::updateCamera(QString &cameraName)
{
    mCameraName = cameraName;
    if(mCameras->isOpened(cameraName)){
        initParams(cameraName);
        ui->widget->show();
        ui->lab_Tips->hide();
    } else {
        ui->widget->hide();
        ui->lab_Tips->show();
    }
}


void ParamDock::on_hs_gain_valueChanged(int value)
{
    ui->sbx_gain->setValue(value);
}

void ParamDock::on_sbx_gain_valueChanged(int arg1)
{
    ui->hs_gain->setValue(arg1);
    mCameras->setGain(mCameraName, arg1);
}

void ParamDock::on_hs_exposure_valueChanged(int value)
{
    ui->sbx_exposure->setValue(value);
}

void ParamDock::on_sbx_exposure_valueChanged(int arg1)
{
    ui->hs_exposure->setValue(arg1);
    mCameras->setExposureTime(mCameraName, arg1);
}

void ParamDock::on_hs_frameRate_valueChanged(int value)
{
    ui->sbx_frameRate->setValue(value);
}

void ParamDock::on_sbx_frameRate_valueChanged(int arg1)
{
    ui->hs_frameRate->setValue(arg1);
    mCameras->setAcquisitionFrameRate(mCameraName, arg1);
}

void ParamDock::on_hs_width_valueChanged(int value)
{
    ui->sbx_width->setValue(value);
}

void ParamDock::on_sbx_width_valueChanged(int arg1)
{
    ui->hs_width->setValue(arg1);
    mCameras->setWidth(mCameraName, arg1);
}

void ParamDock::on_hs_height_valueChanged(int value)
{
    ui->sbx_height->setValue(value);
}

void ParamDock::on_sbx_height_valueChanged(int arg1)
{
    ui->hs_height->setValue(arg1);
    mCameras->setHeight(mCameraName, arg1);
}

void ParamDock::on_hs_xoffset_valueChanged(int value)
{
    ui->sbx_xoffset->setValue(value);
}

void ParamDock::on_sbx_xoffset_valueChanged(int arg1)
{
    ui->hs_xoffset->setValue(arg1);
    mCameras->setoffsetX(mCameraName, arg1);
}

void ParamDock::on_hs_yoffset_valueChanged(int value)
{
    ui->sbx_yoffset->setValue(value);
}

void ParamDock::on_sbx_yoffset_valueChanged(int arg1)
{
    ui->hs_yoffset->setValue(arg1);
    mCameras->setoffsetY(mCameraName, arg1);
}

void ParamDock::initParams(QString &name)
{
    // 通过名称找对应的编号
    QString path = QDir::currentPath();
    QSettings settings(QString("%1/camera/camera.cfg").arg(path), QSettings::IniFormat);
    for (int id = 0; id < 17; ++id) {
        settings.beginGroup(QString("Camera%1").arg(id));
        QString cameraName = settings.value("FriendlyName").toString();
        if (cameraName == name) {
            ui->sbx_Num->setValue(id);
            // 该相机对应的视场
            int fov = settings.value("FOV").toInt();
            ui->sbx_fov->setValue(fov);
        }
        settings.endGroup();
    }

    // 加载配置
    QString fileName = QString("%1/camera/%2.pfs").arg(path).arg(name);

    if (QFile(fileName).exists()){
        mCameras->load(name, fileName);
    }


    // 根据编号加载对应的配置信息
    {
        // Gain
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getGain(name, minValue, value, maxValue, inc);
        ui->hs_gain->setMinimum(minValue);
        ui->hs_gain->setValue(value);
        ui->hs_gain->setMaximum(maxValue);
        ui->hs_gain->setSingleStep(inc);

        ui->sbx_gain->setMinimum(minValue);
        ui->sbx_gain->setValue(value);
        ui->sbx_gain->setMaximum(maxValue);
        ui->sbx_gain->setSingleStep(inc);
    }

    {
        // 帧率的初始化
        double minValue = 1;
        double maxValue = 0;
        double value = 0;
        double inc = 1;

        mCameras->getAcquisitionFrameRate(name, minValue, value, maxValue, inc);
        if (minValue < 1) {
            ui->hs_frameRate->setMinimum(1);
            ui->sbx_frameRate->setMinimum(1);
        } else {
            ui->hs_frameRate->setMinimum(minValue);
            ui->sbx_frameRate->setMinimum(minValue);
        }

        ui->hs_frameRate->setValue(value);
        ui->hs_frameRate->setMaximum(maxValue);
        ui->hs_frameRate->setSingleStep(inc);

        ui->sbx_frameRate->setValue(value);
        ui->sbx_frameRate->setMaximum(maxValue);
        ui->sbx_frameRate->setSingleStep(inc);
    }

    {
        // ExposureTime
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getExposureTime(name, minValue, value, maxValue, inc);
        ui->hs_exposure->setMinimum(minValue);
        ui->hs_exposure->setValue(value);
        ui->hs_exposure->setMaximum(maxValue);
        ui->hs_exposure->setSingleStep(inc);

        ui->sbx_exposure->setMinimum(minValue);
        ui->sbx_exposure->setValue(value);
        ui->sbx_exposure->setMaximum(maxValue);
        ui->sbx_exposure->setSingleStep(inc);
    }

    {
        // Width
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getWidth(name, minValue, value, maxValue, inc);
        ui->hs_width->setMinimum(minValue);
        ui->hs_width->setValue(value);
        ui->hs_width->setMaximum(maxValue);
        ui->hs_width->setSingleStep(inc);

        ui->sbx_width->setMinimum(minValue);
        ui->sbx_width->setValue(value);
        ui->sbx_width->setMaximum(maxValue);
        ui->sbx_width->setSingleStep(inc);
    }

    {
        // Height
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getHeight(name, minValue, value, maxValue, inc);
        ui->hs_height->setMinimum(minValue);
        ui->hs_height->setValue(value);
        ui->hs_height->setMaximum(maxValue);
        ui->hs_height->setSingleStep(inc);

        ui->sbx_height->setMinimum(minValue);
        ui->sbx_height->setValue(value);
        ui->sbx_height->setMaximum(maxValue);
        ui->sbx_height->setSingleStep(inc);
    }

    {
        // offsetX
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getoffsetX(name, minValue, value, maxValue, inc);
        ui->hs_xoffset->setMinimum(minValue);
        ui->hs_xoffset->setValue(value);
        ui->hs_xoffset->setMaximum(maxValue);
        ui->hs_xoffset->setSingleStep(inc);

        ui->sbx_xoffset->setMinimum(minValue);
        ui->sbx_xoffset->setValue(value);
        ui->sbx_xoffset->setMaximum(maxValue);
        ui->sbx_xoffset->setSingleStep(inc);
    }

    {
        // offsetY
        qint64 minValue = 0;
        qint64 maxValue = 0;
        qint64 value = 0;
        qint64 inc = 0;

        mCameras->getoffsetY(name, minValue, value, maxValue, inc);
        ui->hs_yoffset->setMinimum(minValue);
        ui->hs_yoffset->setValue(value);
        ui->hs_yoffset->setMaximum(maxValue);
        ui->hs_yoffset->setSingleStep(inc);

        ui->sbx_yoffset->setMinimum(minValue);
        ui->sbx_yoffset->setValue(value);
        ui->sbx_yoffset->setMaximum(maxValue);
        ui->sbx_yoffset->setSingleStep(inc);
    }
}

void ParamDock::on_btn_save_clicked()
{
    // 保存参数
    // 编号
    int id = ui->sbx_Num->value();
    // 相机对应的视场
    int fov = ui->sbx_fov->value();
    // 增益
    int gain = ui->sbx_gain->value();
    // 帧率
    int frameRate = ui->sbx_frameRate->value();
    // 曝光时间
    int exposure = ui->sbx_exposure->value();
    // 图片格式
    QString pixFormat = ui->cbx_pixFormat->currentText();
    // AOI
    int width = ui->sbx_width->value();
    int height = ui->sbx_height->value();
    int offsetX = ui->sbx_xoffset->value();
    int offsetY = ui->sbx_yoffset->value();

//    mCameraName = "12ftdcs";
    QString path = QDir::currentPath();
    QSettings settings(QString("%1/camera/camera.cfg").arg(path), QSettings::IniFormat);
    settings.beginGroup(QString("Camera%1").arg(id));
    settings.setValue("FriendlyName", mCameraName);
    settings.setValue("FOV", fov);
    settings.setValue("GainRaw", gain);
    settings.setValue("AcquisitionFrameRateAbs", frameRate);
    settings.setValue("ExposureTimeRaw", exposure);
    settings.setValue("PixelFormat", pixFormat);
    settings.setValue("Width", width);
    settings.setValue("Height", height);
    settings.setValue("OffsetX", offsetX);
    settings.setValue("OffsetY", offsetY);
    settings.endGroup();

    mCameras->save(mCameraName);
}

void ParamDock::on_cbx_pixFormat_currentTextChanged(const QString &arg1)
{
    mCameras->setPixelFormat(mCameraName, arg1);
}
