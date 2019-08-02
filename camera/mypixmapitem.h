#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H
#include <QGraphicsPixmapItem>

class MyPixmapItem : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 5 };

    MyPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYPIXMAPITEM_H
