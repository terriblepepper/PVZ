#include "peashot.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include<QMediaPlayer>
peashot::peashot(int attack, bool flag)
    : atk(attack), snow(flag), speed(360.0 * (33333 / fpsIndex) / 1000000)
{
    currentPixmap = QPixmap(snow ? "./images/PeaSnow.png" : "./images/Pea.png");
}


QRectF peashot::boundingRect() const
{
    // 设置豌豆射手的边界矩形
    return QRectF(-12, -28, 24, 24);
}

bool peashot::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    // 当豌豆射手与僵尸碰撞时，返回true
    return other->type() == zombie::Type && qAbs(other->y()- y())<20 && qAbs(other->x() - x()) < 5;
}

void peashot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->drawPixmap(QRect(-12, -28, 24, 24), currentPixmap);
}


void peashot::advance(int phase)
{
    if (!phase)
        return;
    // 检测豌豆射手与其他物体是否发生碰撞
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        // 当豌豆射手与僵尸碰撞时
        zombie *zom = qgraphicsitem_cast<zombie *>(items[qrand() % items.size()]);
        zom->hp -= atk; // 减少僵尸的生命值，受到豌豆射手的攻击

        // 如果豌豆射手带有冰冻效果，且僵尸没被冻
        if (snow && zom->isSnow==false)
        {
            zom->isSnow = true;
            zom->speed /= 2;
        } // 将僵尸的速度减少为原来的1/2
        if (mapScenes[scene()].soundsCount < maxSounds)
        {
            QMediaPlayer* soundpea = new QMediaPlayer(scene());
            soundpea->setMedia(QUrl::fromLocalFile("./sound/kernelpult.mp3"));
            soundpea->setVolume(itemVolume);
            soundpea->play();
            QGraphicsScene* catchScene = scene();
            mapScenes[catchScene].count++;
            mapScenes[catchScene].soundsCount++;
            connect(soundpea, &QMediaPlayer::stateChanged, [soundpea, catchScene](QMediaPlayer::State state) {
                if (state == QMediaPlayer::StoppedState) {
                    if (mapScenes[catchScene].isValid != false) {
                        delete soundpea;
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
            soundpea->play();
        }
        delete this; // 删除豌豆射手对象
        return;
    }
    setX(x() + speed); // 更新豌豆射手的位置，让其向前移动
    update(); // 更新豌豆射手的绘制
    // 如果豌豆射手的位置超过屏幕边界（x > 1069），则删除豌豆射手对象
    if (x() > 1069)
        delete this;
}

void peashot::addAtk(double att)
{
    atk = atk + att;
}

void peashot::setImage(const QString& filePath)
{
    currentPixmap = QPixmap(filePath);
    update(); // 更新绘制
}
