#include "screenzombie.h"
#include "gameIndex.h"
ScreenZombie::ScreenZombie()
{
    hp = 1370.0;
    atk = 100.0 / (30 * (double)fpsIndex);
    speed = 40.0 * (33333.0 / (double)fpsIndex) / 1000000.0 / 4.7;
    zmSound = new QMediaPlayer;
    zmSoundList = new QMediaPlaylist;
    zmSoundList->addMedia(QUrl::fromLocalFile("./sound/Eat.wav"));
    zmSoundList->setPlaybackMode(QMediaPlaylist::Loop);
    zmSound->setMedia(zmSoundList);
    setMovie(":/images/ScreenZombieWalk.gif");
}

void ScreenZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            zmSound->stop();
            setMovie(":/new/prefix1/ZombieDie.gif");
            setHead(":/new/prefix1/ZombieHead.gif");
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        plant *pl = qgraphicsitem_cast<plant *>(items[0]);
        pl->hp -= atk;
        if (state != 1)
        {
            state = 1;
            zmSound->play();
            setMovie(":/new/prefix1/ScreenZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        zmSound->stop();
        setMovie(":/new/prefix1/ScreenZombieWalk.gif");
    }
    setX(x() - speed);
}
