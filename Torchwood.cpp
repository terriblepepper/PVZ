#include "Torchwood.h"
#include "peashot.h"
#include"gameIndex.h"
Torchwood::Torchwood()
{
    hp = 300.0; 
    setMovie(":/new/prefix1/newPlants/Torchwood/idle.gif");
    setScale(2);
}

void Torchwood::advance(int phase)
{
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        foreach(QGraphicsItem * item, items)
        {
            peashot* pea = qgraphicsitem_cast<peashot*>(item);
            pea->addAtk(15.0);
            pea->setImage(":/new/prefix1/FirePea.gif");
        }
    }
}

bool Torchwood::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == peashot::Type && qAbs(pos().x()- other->pos().x())<1 && qAbs(pos().y() - other->pos().y())<15;
}
