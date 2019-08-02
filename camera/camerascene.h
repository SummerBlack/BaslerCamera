#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QColor;
class QRubberBand;
class MyPixmapItem;

QT_END_NAMESPACE

class CameraScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CameraScene(QObject *parent = 0);

    ~CameraScene();
    /**
     * @brief 更新显示的图片
     * @param image
     */
    void updateImage(const QImage &image);

    /**
     * @brief 当前显示的图像
     * @param image
     * @return
     */
    bool getImage(QImage &image);
    /**
     * @brief 更新矩形框的大小和位置
     * @param rect
     * @param pos
     */
    void updateRect(QRectF &rect, const QPointF &pos);

    /**
     * @brief 显示网格
     * @param flag
     */
    void showGrid(bool flag, double scale);

    /**
     * @brief 只显示图像
     */
    void showCameraOnly();
protected:
    /**
     * @brief 鼠标移动事件，主要用于显示鼠标当前位置对应图像的像素
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private slots:

    void handleSceneRectChanged(const QRectF &rect);
signals:
    void sigImageInfo(QPoint point, QRgb rgb);
private:
    void insertImage(const QImage &image);
    /**
     * @brief 初始化界面中所有的Item
     */
    void initItems();
    /**
     * @brief 当界面的大小变化时，更新各个Item的位置
     */
    void updateItemPos();
    /**
     * @brief 更新矩形框与scene中心的偏差
     * @param x
     * @param y
     */
    void updateXYInfo(qreal x, qreal y);
private:
    const static QSizeF SIZE;
    // 采集的图像
    MyPixmapItem *mImageItem = NULL;
    // 两条中心线
    QGraphicsLineItem mTLine;
    QGraphicsLineItem mSLine;
    // 显示中心线的文字
    QGraphicsTextItem mS;
    QGraphicsTextItem mT;
    // 显示图片的偏心距离
    QGraphicsTextItem mXInfo;
    QGraphicsTextItem mYInfo;
    // 矩形框
    QGraphicsRectItem mRect;
};

#endif // CAMERASCENE_H
