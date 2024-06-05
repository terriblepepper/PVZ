#include "BowlingNut.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>

BowlingNut::BowlingNut()
    :atk(350), speed(320.0 * (33333. / (double)fpsIndex) / 1000000.)
{
    hp = 10000.;
    setMovie("./images/BowlingNut.gif");
    mQMovie->setSpeed(250);
}

bool BowlingNut::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 5;
}

void BowlingNut::advance(int phase)
{
    if (!phase)
        return;
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        QMediaPlayer* sound = new QMediaPlayer(scene());
        sound->setMedia(QUrl::fromLocalFile("./sound/bowlingimpact.mp3"));
        sound->setVolume(itemVolume);
        sound->play();
        QGraphicsScene* catchScene = scene();
        mapScenes[catchScene].count++;
        QTimer::singleShot(1500, [sound, catchScene]()
            {
                if (mapScenes[catchScene].isValid != false)
                {
                    delete sound;
                    mapScenes[catchScene].count--;
                }
                else
                {
                    if (mapScenes[catchScene].count)
                    {
                        mapScenes[catchScene].count--;
                    }
                    if (mapScenes[catchScene].count == 0)
                    {
                        mapScenes.erase(catchScene);
                    }
                }
            });
        zombie* zom = qgraphicsitem_cast<zombie*>(items[qrand() % items.size()]);
        zom->hp -= atk; // 减少僵尸的生命值
    }
    setX(x() + speed); // 更新位置，让其向前移动
    update();
    // 如果位置超过屏幕边界（x > 1069），则删除对象
    if (x() > 1069)
        delete this;
}

