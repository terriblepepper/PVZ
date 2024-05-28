#include "sunflower.h"
#include"gameIndex.h"
sunflower::sunflower()
{
    hp = 300.0;
    time = int(10.0 * 1000000 / (33333 / fpsIndex));
    setMovie(":/new/prefix1/SunFlower.gif");
}
void sunflower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        scene()->addItem(new sun(pos()));
    }
}
