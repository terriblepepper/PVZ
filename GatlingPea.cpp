#include"GatlingPea.h"
#include "pea.h"
#include "zombie.h"
#include "peashot.h"
#include"gameIndex.h"

GatlingPea::GatlingPea()
{
    hp = 350.0; // 设置豌豆射手的生命值为200
    atk = 25.0; // 设置豌豆射手的攻击力为25
    time = int(1.4 * 1000000 / (33333 / fpsIndex)); // 计算豌豆射手攻击间隔的帧数，1.4秒对应的帧数（33333/fpsIndex为帧间隔）
    setMovie(":/new/prefix1/newPlants/GatlingPea/idle.gif"); // 设置豌豆射手的动画
    setScale(2);
}

void GatlingPea::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新豌豆射手的绘制
    if ((int)hp <= 0)
        delete this; // 如果豌豆射手的生命值小于等于0，删除豌豆射手对象
    else if (++counter >= time) // 每过一个攻击间隔的帧数
    {
        counter = 0; // 重置计数器
        // 如果豌豆射手与其他图形项发生碰撞（即僵尸在豌豆射手的攻击范围内）
        if (!collidingItems().isEmpty())
        {
            peashot* pe = new peashot(atk);
            pe->setX(x() + 30);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 60);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 90);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 120);
            pe->setY(y());
            scene()->addItem(pe);
            return;
        }
    }
}

bool GatlingPea::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        // 当豌豆射手与僵尸在同一纵坐标上（y相等）发生碰撞时，返回true
        return other->type() == zombie::Type && qFuzzyCompare(other->y(), y());
}
