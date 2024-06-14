#include "TwinSunflower.h"
#include"gameIndex.h"
TwinSunflower::TwinSunflower()
{
    hp = 300.0;
    setMovie(":/new/prefix1/newPlants/TwinSunflower/idle.gif");
    setScale(2);
}

void TwinSunflower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else
    {
        time = (int)((qrand() % 20 + 15) * 1000000. / (33333. / (double)fpsIndex));
        if (++counter >= time)
        {
            counter = 0;
            QPointF pos1(pos().x()-30,pos().y()-20);
            scene()->addItem(new sun(pos1));
        }
        time = (int)((qrand() % 20 + 8) * 1000000. / (33333. / (double)fpsIndex));
        if (++counter >= time)
        {
            counter = 0;
            QPointF pos2(pos().x() + 30, pos().y());
            scene()->addItem(new sun(pos2));
        }
    }
}
