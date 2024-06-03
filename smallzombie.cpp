#include "smallzombie.h"
#include"gameIndex.h"
#include<QDebug>
#include"adventureMode.h"
smallzombie::smallzombie()
{
    hp = 270.0; 
    atk = 125.0 / (30 * (double)fpsIndex);
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0; 
    if (adventureGameMode::level < 16 && adventureGameMode::level>10)
    {
        setMovie(":/new/prefix2/images/newZombies/small2/walk.gif");

    }
    else
    {
        setMovie(":/new/prefix1/newZombies/small/walk.gif");
    }
    
    setScale(0.7);
}

void smallzombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0) 
    {
        if (state < 2) 
        {
            state = 2; // ��״̬����Ϊ2��������
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/small2/death.gif");

            }
            else
            {
                setMovie(":/new/prefix1/newZombies/small/death.gif");
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
        qInfo() << "basicAtk" << atk;
        if (state != 1) 
        {
            state = 1; // ��״̬����Ϊ1��������
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie(":/new/prefix2/images/newZombies/small2/eat.gif");

            }
            else
            {
                setMovie(":/new/prefix1/newZombies/small/eat.gif");
            }
        }
        return;
    }
    if (state) 
    {
        state = 0; // ��״̬����Ϊ0�����ߣ�
        if (adventureGameMode::level < 16 && adventureGameMode::level>10)
        {
            setMovie(":/new/prefix2/images/newZombies/small2/walk.gif");

        }
        else
        {
            setMovie(":/new/prefix1/newZombies/small/walk.gif");
        }
    }
    setX(x() - speed); 
}
