#include "snowpea.h"
#include "peashot.h"
#include "zombie.h"
#include"gameIndex.h"
#include<QMediaPlayer>
snowpea::snowpea()
{
    atk = 25.0;
    hp = 300.0;
    time = int(1.4 * 1000000 * fpsIndex / 33333);
    setMovie(":/new/prefix1/SnowPea.gif");
}
void snowpea::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
            peashot *pe = new peashot(atk, true);
            pe->setX(x() + 30);
            pe->setY(y());
            scene()->addItem(pe);
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
            }
            return;
        }
    }
}
bool snowpea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(other->y() - y()) < 30;
}
