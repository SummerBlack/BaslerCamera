#include "mypixmapitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
MyPixmapItem::MyPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{

}

void MyPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF itemPos = event->pos();
    QPointF scenePos = mapToScene(itemPos);
    QPointF viewPos = mapFromScene(scenePos);
    qDebug() << "ItemPos:" << itemPos;
    qDebug() << "scenePos:" << scenePos;
    qDebug() << "viewPos:" << viewPos;
//    QImage image = pixmap().toImage();
//    QPoint pos = itemPos.toPoint();
//    QRgb rgb = image.pixel(pos);
////    emit sigImageInfo(pos, rgb);
//    qDebug() << "R: " << qRed(rgb) << "G: "<< qGreen(rgb) << "B: "<< qBlue(rgb);
}
