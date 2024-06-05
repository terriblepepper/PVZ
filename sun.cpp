#include "sun.h"
#include "shop.h"
#include"gameIndex.h"

sun::sun()
    :iscollected(false)
{

    dest = QPoint(200 + qrand() % 200, 200 + qrand() % 200);
    setPos(QPointF(dest.x(), 70));
    speed =  75. / (30. * (double)fpsIndex);
    counter = 0;
    time = int(25.0 * 30 * fpsIndex);
    movie = new QMovie(":/new/prefix1/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

sun::sun(QPointF pos)
    :iscollected(false)
{
    dest = QPointF(pos.x() + qrand() % 60, pos.y() + qrand() % 60);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 30. / (30. * (double)fpsIndex);
    counter = 0;
    time = int(25.0 * 30 * fpsIndex);
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

    if (!iscollected)
    {
        shop* sh = qgraphicsitem_cast<shop*>(scene()->items(QPointF(300, 15))[0]);
        if (!sh)return;
        sh->sunnum += 50;
        dest = QPointF(300, 40);
        speed = 280. / (30. * (double)fpsIndex);
        iscollected = true;
        QMediaPlayer* sound = new QMediaPlayer();
        sound->setMedia(QUrl::fromLocalFile("./sound/points.mp3"));
        sound->setVolume(itemVolume);
        sound->play();
        QGraphicsScene* catchScene = scene();
        mapScenes[catchScene].count++;
        mapScenes[catchScene].soundsCount++;
        connect(sound, &QMediaPlayer::stateChanged, [sound, catchScene](QMediaPlayer::State state) {
            if (state == QMediaPlayer::StoppedState) {
                if (mapScenes[catchScene].isValid != false) {
                    delete sound;
                    mapScenes[catchScene].count--;
                    mapScenes[catchScene].soundsCount--;
                    return;
                }
                else {
                    if (mapScenes[catchScene].count) {
                        mapScenes[catchScene].count--;
                    }
                    if (mapScenes[catchScene].count == 0) {
                        mapScenes.erase(catchScene);
                    }
                }
            }
            });
        event->setAccepted(true);
    }   
}
void sun::advance(int phase)
{
    if (!phase)
        return;
    update();

    QLineF l(pos(),dest);
    if (++counter >= time || (l.length()<=30 && iscollected))
        delete this;
    else
    {
        setPos(QPointF(pos().x() + speed * qCos(qDegreesToRadians(l.angle())), pos().y() - speed * qSin(qDegreesToRadians(l.angle()))));
        //回收阳光时阳光移动越久速度越快
        if(counter%fpsIndex == 0 && iscollected)speed *= 1.1;
    }
}

