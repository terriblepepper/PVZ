#include "sun.h"
#include "shop.h"
#include"gameIndex.h"

sun::sun()
{

    dest = QPoint(200 + qrand() % 200, 200 + qrand() % 200);
    setPos(QPointF(dest.x(), 70));
    speed = 20.0 * 50 / (1000000.0 * (double)fpsIndex);
    counter = 0;
    time = int(10.0 * 1000000.0 * (double)fpsIndex / 33333);
    movie = new QMovie(":/new/prefix1/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

sun::sun(QPointF pos)
{
    dest = QPointF(pos.x() + qrand() % 30, pos.y() + qrand() % 30);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 20 * 50 / (1000000 * fpsIndex);
    counter = 0;
    time = int(10.0 * 1000000 * fpsIndex / 33333);
    movie = new QMovie(":/new/prefix1/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}
sun::~sun()
{
    if (movie)
        delete movie;
}
QRectF sun::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}
void sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(),movie->currentImage());
}
void sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    shop *sh = qgraphicsitem_cast<shop *>(scene()->items(QPointF(300, 15))[0]);
    sh->sunnum += 25;
    counter = time;
    event->setAccepted(true);
}
void sun::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
        delete this;
    else if (y() < dest.y())
        setY(y() + speed);
}