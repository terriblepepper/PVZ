#include"flagzombie.h"
#include"gameIndex.h"
#include"adventureMode.h"

flagzombie::flagzombie()
{
    hp = 270.0; 
    atk = 100.0 / (30 * (double)fpsIndex);
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0;
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
        setMovie(":/new/prefix1/newZombies/flag/walk.gif"); 
    }
    
    setScale(1.2);
}

void flagzombie::advance(int phase)
{
    if (!phase)
        return;
    update(); 
    if (hp <= 0) 
    {
        if (state < 2) 
        {
            state = 2; // 将状态设置为2（死亡）
            zmSound->stop();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/flag2/death.gif");
            }
            else
            {
                setMovie(":/new/prefix1/ZombieDie.gif"); 
                setHead(":/new/prefix1/ZombieHead.gif"); 
            }
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; 
        return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty()) 
    {
        plant* pl = qgraphicsitem_cast<plant*>(items[0]);
        pl->hp -= atk; 
        if (state != 1) 
        {
            state = 1; // 将状态设置为1（攻击）
            zmSound->play();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/flag2/eat.gif");
            }
            else
            {
                setMovie(":/new/prefix1/newZombies/flag/eat.gif");
            }
        }
        return;
    }
    if (state) 
    {
        state = 0; // 将状态设置为0（行走）
        zmSound->stop();
        if (adventureGameMode::level < 16 && adventureGameMode::level>10)
        {
            setMovie(":/new/prefix2/images/newZombies/flag2/walk.gif");
        }
        else
        {
            setMovie(":/new/prefix1/newZombies/flag/walk.gif");
        }
    }
    setX(x() - speed); 
}
