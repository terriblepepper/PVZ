#include "CaiWen.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
CaiWen::CaiWen()
{
    hp = 450.0;
    atk = 25.0;
    time = int(0.5 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/CaiWen/idle.gif");
    setScale(2);
}

void CaiWen::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time) // ÿ��һ�����������֡��
    {
        counter = 0; // ���ü�����
        QList<QGraphicsItem*> items = collidingItems();
        //����н�ʬ���빥����Χ
        if (!items.isEmpty())
        {
            setMovie(":/new/prefix1/newPlants/CaiWen/shooting.gif");
            foreach(QGraphicsItem * item, items)
            {
                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/CaiWen/idle.gif");
        }
    }
}

bool CaiWen::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 140 && pos().y() == other->pos().y();
}
