#include "sunflower.h"
#include"gameIndex.h"
sunflower::sunflower()
{
    hp = 300.0;
    setMovie(":/new/prefix1/SunFlower.gif");
}
void sunflower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else 
    {
        time = (int)((qrand() % 15 + 8) * 1000000. / (33333. / (double)fpsIndex));//将生产阳光时间随机化
        if (++counter >= time) 
        {
            counter = 0;
            scene()->addItem(new sun(pos()));
        }
    }
}
