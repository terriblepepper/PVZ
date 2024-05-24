#include "sunflower.h"
#include"gameIndex.h"
sunflower::sunflower()
{
    hp = 300;
    time = int(10.0 * 1000 / (33 / fpsIndex));
    setMovie(":/new/prefix1/SunFlower.gif");
}
void sunflower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        scene()->addItem(new sun(pos()));
    }
}
