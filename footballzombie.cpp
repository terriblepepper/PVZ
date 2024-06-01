#include "footballzombie.h"
#include"gameIndex.h"
FootballZombie::FootballZombie()
{
    hp = 1670.0;
    atk = 100.0 * (33333.0 / (double)fpsIndex) / 1000000.0;
    speed = 60.0 * (33333.0 / (double)fpsIndex) / 1000000.0 / 2.5;
    setMovie(":/new/prefix1/FootballZombieWalk.gif");
}

void FootballZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/new/prefix1/FootballZombieDie.gif");
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
            setMovie(":/new/prefix1/FootballZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        setMovie(":/new/prefix1/FootballZombieWalk.gif");
    }
    setX(x() - speed);
}
