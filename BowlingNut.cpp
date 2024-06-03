#include "BowlingNut.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>

BowlingNut::BowlingNut()
    :atk(350), speed(320.0 * (33333. / (double)fpsIndex) / 1000000.)
{
    hp = 10000.;
    setMovie("./images/BowlingNut.gif");
    mQMovie->setSpeed(250);
}

bool BowlingNut::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(other->y() - y()) < 30 && qAbs(other->x() - x()) < 5;
}

void BowlingNut::advance(int phase)
{
    if (!phase)
        return;
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        // 当豌豆射手与僵尸碰撞时
        zombie* zom = qgraphicsitem_cast<zombie*>(items[qrand() % items.size()]);
        zom->hp -= atk; // 减少僵尸的生命值
    }
    setX(x() + speed); // 更新位置，让其向前移动
    // 如果位置超过屏幕边界（x > 1069），则删除对象
    if (x() > 1069)
        delete this;
}

