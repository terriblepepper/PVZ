#include "FumeShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
FumeShroom::FumeShroom()
{
    hp = 300.0; 
    atk = 25.0; 
    time = int(1.4 * 1000000. / (33333. / (double)fpsIndex)); 
    setMovie(":/new/prefix1/newPlants/FumeShroom/idle.gif"); 
    setScale(1.2);
}

void FumeShroom::advance(int phase)
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
            setMovie(":/new/prefix1/newPlants/FumeShroom/shooting.gif");
            foreach(QGraphicsItem * item, items)
            {
                // 在大喷菇右侧30像素处生成泡泡动画
                QGraphicsPixmapItem* bubble = new QGraphicsPixmapItem();
                bubble->setPixmap(QPixmap(":/new/prefix1/Bubbles.gif"));
                bubble->setPos(pos().x() + 75, pos().y() - 24);
                bubble->setScale(2);
                scene()->addItem(bubble);
                QGraphicsScene* catchScene = scene();
                mapScenes[catchScene].count++;
                QTimer::singleShot(800, [bubble, catchScene]() {
                    if (mapScenes[catchScene].isValid != false)
                    {
                        delete bubble;
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
                if (mapScenes[catchScene].soundsCount < maxSounds)
                {
                    mapScenes[catchScene].count++;
                    mapScenes[catchScene].soundsCount++;
                    QMediaPlayer* soundbubble = new QMediaPlayer(scene());
                    soundbubble->setMedia(QUrl::fromLocalFile("./sound/fume.mp3"));
                    soundbubble->setVolume(itemVolume);
                    soundbubble->play();
                    // 设置泡泡音频删除连接
                    connect(soundbubble, &QMediaPlayer::stateChanged, [soundbubble, catchScene](QMediaPlayer::State state) {
                        if (state == QMediaPlayer::StoppedState) {
                            if (mapScenes[catchScene].isValid != false) {
                                delete soundbubble;
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
                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/FumeShroom/idle.gif");
        }
    }
}

bool FumeShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 200 && qAbs( pos().y() - other->pos().y())<25 && other->pos().x() > pos().x();
}
