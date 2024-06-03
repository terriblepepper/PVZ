#include "DoublePea.h"
#include"gameIndex.h"
DoublePea::DoublePea()
{
    atk = 25.0;
    hp = 300.0;
    time = int(1.4 * 1000000 / (33333 / fpsIndex));
    setMovie(":/new/prefix1/DoublePea.gif");
}

void DoublePea::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        QList<QGraphicsItem *> items = collidingItems();
        if (!collidingItems().isEmpty())
        {
            peashot *pe = new peashot(atk);
            pe->setX(x() + 30);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 60);
            pe->setY(y());
            scene()->addItem(pe);
            return;
        }
    }
}

bool DoublePea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == zombie::Type && qAbs(other->y()- y())<30;
}
