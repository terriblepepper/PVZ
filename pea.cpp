#include "pea.h"
#include "zombie.h"
#include "peashot.h"
#include"gameIndex.h"
#include<QMediaPlayer>
pea::pea()
{
    hp = 200.0; // 设置豌豆射手的生命值为200
    atk = 25.0; // 设置豌豆射手的攻击力为25
    time = int(1.4 * 1000000. / (33333. / (double)fpsIndex)); // 计算豌豆射手攻击间隔的帧数，1.4秒对应的帧数（33333/fpsIndex为帧间隔）
    setMovie(":/new/prefix1/Peashooter.gif"); // 设置豌豆射手的动画
}

void pea::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新豌豆射手的绘制
    if ((int)hp <= 0)
        delete this; // 如果豌豆射手的生命值小于等于0，删除豌豆射手对象
    else if (++counter >= time) // 每过一个攻击间隔的帧数
    {
        counter = 0; // 重置计数器
        // 如果豌豆射手与其他图形项发生碰撞（即僵尸在豌豆射手的攻击范围内）
        if (!collidingItems().isEmpty())
        {
            peashot *newshot = new peashot(atk); // 创建一个豌豆射手的子弹对象
            newshot->setX(x() + 30); // 设置子弹的初始位置在豌豆射手的右侧30像素处
            newshot->setY(y()); // 设置子弹的高度与豌豆射手相同
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
            scene()->addItem(newshot); // 将子弹添加到场景中
            return; // 返回，不进行移动
        }
    }
}

bool pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(other->y() - y()) < 30;
}
