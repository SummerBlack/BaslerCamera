#ifndef PARAMDOCK_H
#define PARAMDOCK_H

#include <QWidget>
#include "cameramanager.h"
namespace Ui {
class ParamDock;
}

class ParamDock : public QWidget
{
    Q_OBJECT

public:
    explicit ParamDock(QWidget *parent = 0);
    ~ParamDock();

public slots:
    void updateCamera(QString &cameraName);

private slots:
    void on_hs_gain_valueChanged(int value);

    void on_sbx_gain_valueChanged(int arg1);

    void on_hs_exposure_valueChanged(int value);

    void on_sbx_exposure_valueChanged(int arg1);

    void on_hs_frameRate_valueChanged(int value);

    void on_sbx_frameRate_valueChanged(int arg1);

    void on_hs_width_valueChanged(int value);

    void on_sbx_width_valueChanged(int arg1);

    void on_hs_height_valueChanged(int value);

    void on_sbx_height_valueChanged(int arg1);

    void on_hs_xoffset_valueChanged(int value);

    void on_sbx_xoffset_valueChanged(int arg1);

    void on_hs_yoffset_valueChanged(int value);

    void on_sbx_yoffset_valueChanged(int arg1);
    void on_btn_save_clicked();

    void on_cbx_pixFormat_currentTextChanged(const QString &arg1);

private:
    void initParams(QString &name);
private:
    Ui::ParamDock *ui;
    QString mCameraName;
    CameraManager *mCameras;
};

#endif // PARAMDOCK_H
