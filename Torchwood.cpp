#include "Torchwood.h"
#include "peashot.h"
#include"gameIndex.h"
#include<QMediaPlayer>
Torchwood::Torchwood()
{
    hp = 300.0; 
    setMovie(":/new/prefix1/newPlants/Torchwood/idle.gif");
    setScale(2);
}

void Torchwood::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else
    {
        QList<QGraphicsItem*> items = collidingItems();
        if (!items.isEmpty())
        {
            foreach(QGraphicsItem * item, items)
            {
                QMediaPlayer* sound = new QMediaPlayer();
                sound->setMedia(QUrl::fromLocalFile("./sound/firepea.mp3"));
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
                peashot* pea = qgraphicsitem_cast<peashot*>(item);
                pea->addAtk(15.0);
                pea->setImage(":/new/prefix1/FirePea.gif");
            }
        }
    }
}

bool Torchwood::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == peashot::Type && qAbs(pos().x()- other->pos().x())<2 && qAbs(pos().y() - other->pos().y())<30;
}
