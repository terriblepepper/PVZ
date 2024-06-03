#include"apolozombie.h"
#include"gameIndex.h"


apolozombie::apolozombie()
{
    hp = 420;
    atk = 100.0 / (30 * (double)fpsIndex);
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0;
    setMovie("./images/newZombies/apolo/walk.gif");
    //setScale(1.27);
}

void apolozombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2; // 将状态设置为2（死亡）

            setMovie("./images/newZombies/apolo/death.gif");
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
            setMovie("./images/newZombies/apolo/eat.gif");
        }
        return;
    }
    if (state)
    {
        state = 0; // 将状态设置为0（行走）
        setMovie("./images/newZombies/apolo/walk.gif");
    }
    setX(x() - speed);
}
