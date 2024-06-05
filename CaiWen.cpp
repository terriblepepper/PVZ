#include "CaiWen.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
CaiWen::CaiWen()
{
    hp = 450.0;
    atk = 25.0;
    time = int(0.5 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/CaiWen/idle.gif");
    setScale(1.5);
}

void CaiWen::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time) // 每过一个攻击间隔的帧数
    {
        counter = 0; // 重置计数器
        QList<QGraphicsItem*> items = collidingItems();
        //如果有僵尸进入攻击范围
        if (!items.isEmpty())
        {
            setMovie(":/new/prefix1/newPlants/CaiWen/shooting.gif");
            QMediaPlayer* sound = new QMediaPlayer(scene());
            sound->setMedia(QUrl::fromLocalFile("./sound/bonk.mp3"));
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
            foreach(QGraphicsItem * item, items)
            {
                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/CaiWen/idle.gif");
        }
    }
}

bool CaiWen::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 140 && qAbs(pos().y()- other->pos().y())<30;
}
