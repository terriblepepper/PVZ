#include "conezombie.h"
#include"gameIndex.h"
ConeZombie::ConeZombie()
{
    hp = 640.0;
    atk = 100.0 * (33333.0 / (double)fpsIndex) / 1000000.0;
    speed = 40.0 * (33333.0 / (double)fpsIndex) / 1000000.0 / 4.7;
    setMovie(":/new/prefix1/ConeZombieWalk.gif");
}

void ConeZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
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
            setMovie(":/new/prefix1/ConeZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        setMovie(":/new/prefix1/ConeZombieWalk.gif");
    }
    setX(x() - speed);
}
