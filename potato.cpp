#include "potato.h"
#include "zombie.h"
#include"gameIndex.h"
#include<QTimer>
#include<QMediaPlayer>
potato::potato()
{
    atk = 1800.0;//土豆雷直接秒杀
    hp = 300.0;
    time = int(15.0 * 1000000 / (33333.0 / (double)fpsIndex));
    setMovie(":/new/prefix1/PotatoMine1.gif");
}

QRectF potato::boundingRect() const
{
    return state == 2 ? QRectF(-75, -75, 150, 150) : plant::boundingRect();
}

void potato::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (state == 0 && ++counter >= time)
    {
        state = 1;
        counter = 0;
        time = int(1.0 * 1000000 / (33333 / fpsIndex));
        setMovie(":/new/prefix1/PotatoMine.gif");
    }
    else if (state == 1 && ++counter >= time)
    {
        counter = 0;
        QList<QGraphicsItem *> items = collidingItems();
        if (!items.isEmpty())
        {
            state = 2;
            QMediaPlayer* sound = new QMediaPlayer(scene());
            sound->setMedia(QUrl::fromLocalFile("./sound/potato_mine.mp3"));
            sound->setVolume(itemVolume);
            sound->play();
            QGraphicsScene* catchScene = scene();
            mapScenes[catchScene].count++;
            connect(sound, &QMediaPlayer::stateChanged, [sound, catchScene](QMediaPlayer::State state) {
                if (state == QMediaPlayer::StoppedState) {
                    if (mapScenes[catchScene].isValid != false) {
                        delete sound;
                        mapScenes[catchScene].count--;
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
            setMovie(":/new/prefix1/PotatoMineBomb.gif");
            foreach (QGraphicsItem *item, items)
            {
                zombie *zom = qgraphicsitem_cast<zombie *>(item);
                zom->hp -= atk;
                if (zom->hp <= 0)
                    delete zom;
            }
        }
    }
    else if (state == 2 && mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
        delete this;
}

bool potato::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 50;
}
