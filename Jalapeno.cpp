#include"Jalapeno.h"
#include"zombie.h"
#include"gameIndex.h"
#include<QTimer>
#include<QMediaPlayer>
Jalapeno::Jalapeno()
{
	atk = 1800.0;
	hp = 8000.0;
	setMovie(":/new/prefix1/newPlants/Jalapeno/idle.gif");
}

QRectF Jalapeno::boundingRect() const
{
	return state ? QRectF(-150, -150, 300, 300) : plant::boundingRect();
}

void Jalapeno::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (state == 0 && mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
    {
        state = 1;
        QMediaPlayer* sound = new QMediaPlayer();
        sound->setMedia(QUrl::fromLocalFile("./sound/jalapeno.mp3"));
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
        setMovie(":/new/prefix1/newPlants/Jalapeno/explode.gif");
        QList<QGraphicsItem*> items = scene()->items();
        foreach(QGraphicsItem * item, items)
        {
            zombie* zom = qgraphicsitem_cast<zombie*>(item);
            if (zom && qFuzzyCompare(zom->y(), y())) // 同一排的僵尸
            {
                zom->hp -= atk;
                if (zom->hp <= 0)
                {
                    zom->state = 3;
                    zom->setMovie(":/new/prefix1/Burn.gif");
                }
            }
        }
    }
    else if (state == 1 && mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
        delete this;
}

bool Jalapeno::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && QLineF(pos(), other->pos()).length() < 160;
}
