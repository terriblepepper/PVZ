#include "icetrackerzombie.h"
#include"gameIndex.h"
icetrackerzombie::icetrackerzombie()
{
    hp = 2700.0;
    atk = 1680 / (30 * (double)fpsIndex);
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0 ;
    setMovie(":/new/prefix1/newZombies/icetracker/drive.gif");
    setScale(2);
}

void icetrackerzombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/new/prefix1/newZombies/icetracker/wheelie.gif");
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this;
        return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        plant* pl = qgraphicsitem_cast<plant*>(items[0]);
        pl->hp -= atk;
        if (state != 1)
        {
            state = 1;
            setMovie(":/new/prefix1/newZombies/icetracker/drive.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        setMovie(":/new/prefix1/newZombies/icetracker/drive.gif");
    }
    setX(x() - speed);
}

bool icetrackerzombie::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)

        // 当僵尸和植物碰撞时，返回true
        return other->type() == plant::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 125;
}