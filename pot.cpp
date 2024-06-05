#include "pot.h"
#include"gameIndex.h"
Pot::Pot()
{
    hp = 300.0;
    isPot = true;
    setMovie("./images/newPlants/Pot/idle.gif");
    setScale(2.5);
}
void Pot::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
}

QRectF Pot::boundingRect() const
{
    return QRect(-35, -35, 70, 70);
}

QPainterPath Pot::shape() const
{
    // ������ײ��״���������ű仯
    QPainterPath path;
    path.addRect(-17.5, -17.5, 35, 35);  // ��ײ��״����
    return path;
}
