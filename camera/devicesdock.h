#ifndef DEVICESDOCK_H
#define DEVICESDOCK_H

#include <QWidget>
#include <QListWidgetItem>
#include "cameramanager.h"

namespace Ui {
class DevicesDock;
}

class DevicesDock : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesDock(QWidget *parent = 0);
    ~DevicesDock();

private slots:
    void on_btn_search_clicked();

    void handleCameraUpdate(const QStringList &list);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

signals:
    void sigActivated(QString &cameraName);
private:
    Ui::DevicesDock *ui;
    CameraManager *mCameras = NULL;
};

#endif // DEVICESDOCK_H
