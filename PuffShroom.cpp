#include "PuffShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"smallBubble.h"
PuffShroom::PuffShroom()
{
    hp = 250.0;
    atk = 15.0;
    time = int(1.6 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/PuffShroom/idle.gif");
    setScale(1.3);
}

void PuffShroom::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time) // 每过一个攻击间隔的帧数
    {
        counter = 0; // 重置计数器
        if (!collidingItems().isEmpty())
        {
            setMovie(":/new/prefix1/newPlants/PuffShroom/shooting.gif");
            smallBubble* newshot = new smallBubble(atk); 
            newshot->originX = x() + 15;
            newshot->setX(newshot->originX); 
            newshot->setY(y()); // 设置子弹的高度与小喷菇相同
            scene()->addItem(newshot); // 将泡泡添加到场景中
            return; // 返回，不进行移动
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/PuffShroom/idle.gif");
        }
    }
}

bool PuffShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 295 && pos().y() == other->pos().y() && other->pos().x() > pos().x();
}
