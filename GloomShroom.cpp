#include "GloomShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
GloomShroom::GloomShroom()
{
    hp = 350.0;
    atk = 28.0;
    time = int(1.72 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/GloomShroom/idle.gif");
    setScale(1.27);
}

void GloomShroom::advance(int phase)
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
            setMovie(":/new/prefix1/newPlants/GloomShroom/shooting.gif");
            foreach(QGraphicsItem * item, items)
            {
                // 生成泡泡动画
                QGraphicsPixmapItem* bubbleUp = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleDown = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleLeft = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleRight = new QGraphicsPixmapItem();

                QPixmap bubblePixmap(":/new/prefix1/Bubbles.gif");

                bubbleUp->setPixmap(bubblePixmap);
                bubbleDown->setPixmap(bubblePixmap);
                bubbleLeft->setPixmap(bubblePixmap);
                bubbleRight->setPixmap(bubblePixmap);

                QPointF pos = this->pos();

                // 设置泡泡位置
                bubbleUp->setPos(pos.x()-20, pos.y() - 70); 
                bubbleDown->setPos(pos.x()-20, pos.y() + 70); 
                bubbleLeft->setPos(pos.x() - 125, pos.y()); 
                bubbleRight->setPos(pos.x() + 60, pos.y()); 

                // 将泡泡添加到场景中
                scene()->addItem(bubbleUp);
                scene()->addItem(bubbleDown);
                scene()->addItem(bubbleLeft);
                scene()->addItem(bubbleRight);
                QMediaPlayer* soundbubble = new QMediaPlayer(scene());
                soundbubble->setMedia(QUrl::fromLocalFile("./sound/fume.mp3"));
                soundbubble->setVolume(itemVolume);
                soundbubble->play();
                QGraphicsScene* catchScene = scene();
                mapScenes[catchScene].count += 4;
                // 设置定时器，泡泡显示一段时间后删除
                QTimer::singleShot(1000, [soundbubble,bubbleUp,catchScene]()
                    { 
                        if (mapScenes[catchScene].isValid != false)
                        {
                            delete soundbubble;
                            delete bubbleUp;
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
                QTimer::singleShot(1000, [bubbleDown, catchScene]() 
                    {
                        if (mapScenes[catchScene].isValid != false)
                        {
                            delete bubbleDown;
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
                QTimer::singleShot(1000, [bubbleLeft, catchScene]() 
                    { 
                        if (mapScenes[catchScene].isValid != false)
                        {
                            delete bubbleLeft;
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
                QTimer::singleShot(1000, [bubbleRight, catchScene]() 
                    { 
                        if (mapScenes[catchScene].isValid != false)
                        {
                            delete bubbleRight;
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

                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else 
        {
            setMovie(":/new/prefix1/newPlants/GloomShroom/idle.gif");
        }
    }
}

bool GloomShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && QLineF(pos(), other->pos()).length() < 150;
}
