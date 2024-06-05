#include "pot.h"
#include"gameIndex.h"
Pot::Pot()
{
    hp = 300.0;
    isPot = true;
    setMovie("./images/newPlants/Pot/idle.gif");
    setScale(1.2);
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
    // 定义碰撞形状，不随缩放变化
    QPainterPath path;
    path.addRect(-14.5, -14.5, 35, 35);  // 碰撞形状矩形
    return path;
}
