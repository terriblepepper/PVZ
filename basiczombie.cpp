#include "basiczombie.h"
#include"gameIndex.h"
#include"adventureMode.h"
#include<QDebug>
basiczombie::basiczombie()
{
    hp = 270.0; // 设置基础僵尸的生命值为270
    atk = 100.0 / (30 * (double)fpsIndex);// 设置基础僵尸的攻击力为100（每秒攻击100点）
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0; // 设置基础僵尸的速度为5.0像素/秒（16毫秒为帧间隔）
    zmSound = new QMediaPlayer;
    zmSoundList = new QMediaPlaylist;
    zmSoundList->addMedia(QUrl::fromLocalFile("./sound/Eat.wav"));
    zmSoundList->setPlaybackMode(QMediaPlaylist::Loop);
    zmSound->setMedia(zmSoundList);
    if (adventureGameMode::level < 16 && adventureGameMode::level>10)
    {
        setMovie(":/new/prefix2/images/newZombies/flag2/walk.gif");
    }
    else
    {
         setMovie(":/new/prefix1/ZombieWalk1.gif"); 
    }
}

void basiczombie::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新基础僵尸的绘制
    if (hp <= 0) // 如果基础僵尸的生命值小于等于0，表示已经被击败
    {
        if (state < 2) // 如果基础僵尸的状态小于2，表示处于死亡状态
        {
            state = 2; // 将状态设置为2（死亡）
            zmSound->stop();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/flag2/death.gif");
            }
            else
            {
                setMovie(":/new/prefix1/ZombieDie.gif"); // 设置基础僵尸的行走动画
                setHead(":/new/prefix1/ZombieHead.gif"); // 设置基础僵尸的头部掉落动画
            }
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; // 如果基础僵尸的死亡动画播放完毕，删除基础僵尸对象
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()) // 如果基础僵尸与其他图形项发生碰撞
    {
        plant *pl = qgraphicsitem_cast<plant *>(items[0]);
        pl->hp -= atk; // 减少植物的生命值，受到基础僵尸的攻击
        qInfo() << "basicAtk" << atk;
        if (state != 1) // 如果基础僵尸的状态不为1（攻击状态）
        {
            state = 1; // 将状态设置为1（攻击）
            zmSound->play();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/flag2/eat.gif");
            }
            else
            {
                setMovie(":/new/prefix1/ZombieAttack.gif"); 
            }
        }
        return;
    }
    if (state) // 如果基础僵尸的状态不为0（行走状态）
    {
        state = 0; // 将状态设置为0（行走）
        zmSound->stop();
        if (adventureGameMode::level < 16 && adventureGameMode::level>10)
        {
            setMovie(":/new/prefix2/images/newZombies/flag2/walk.gif");
        }
        else
        {
            setMovie(":/new/prefix1/ZombieWalk1.gif");
        }
    }
    setX(x() - speed); // 更新基础僵尸的位置，让其向左移动
}
