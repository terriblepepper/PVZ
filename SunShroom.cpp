#include "SunShroom.h"
#include"gameIndex.h"
SunShroom::SunShroom()
{
    hp = 180.0;
    setMovie(":/new/prefix1/newPlants/SunShroom/bigidle.gif");
}

void SunShroom::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else
    {
        time = (int)((qrand() % 15 + 15)* 1000000. / (33333. / (double)fpsIndex));//����������ʱ�������
        if (++counter >= time)
        {
            counter = 0;
            scene()->addItem(new sun(pos()));
        }
    }
}
