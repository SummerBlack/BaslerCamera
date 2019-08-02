#pragma execution_character_set("utf-8")
#include "devicesdock.h"
#include "ui_devicesdock.h"
#include <QDebug>

DevicesDock::DevicesDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevicesDock),
    mCameras(CameraManager::getInstance())
{
    ui->setupUi(this);
    connect(mCameras, &CameraManager::sigCameraUpdate, this, &DevicesDock::handleCameraUpdate);
}

DevicesDock::~DevicesDock()
{
    qDebug() << "~DevicesDock";
    delete mCameras;
    delete ui;
}

void DevicesDock::on_btn_search_clicked()
{
    mCameras->searchCameras();
}

void DevicesDock::handleCameraUpdate(const QStringList &list)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
}

void DevicesDock::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
//    qDebug() << "itemDoubleClicked" << item->text();
//    QString friendName = item->text();

//    mCameras->openCamera(friendName);
}

void DevicesDock::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << "itemClicked" << item->text();
    emit sigActivated(item->text());
}

