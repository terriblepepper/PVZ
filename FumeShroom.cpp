#include "FumeShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
FumeShroom::FumeShroom()
{
    hp = 300.0; 
    atk = 25.0; 
    time = int(1.4 * 1000000. / (33333. / (double)fpsIndex)); 
    setMovie(":/new/prefix1/newPlants/FumeShroom/idle.gif"); 
    setScale(2);
}

void FumeShroom::advance(int phase)
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
            setMovie(":/new/prefix1/newPlants/FumeShroom/shooting.gif");
            foreach(QGraphicsItem * item, items)
            {
                // �ڴ��繽�Ҳ�30���ش��������ݶ���
                QGraphicsPixmapItem* bubble = new QGraphicsPixmapItem();
                bubble->setPixmap(QPixmap(":/new/prefix1/Bubbles.gif"));
                bubble->setPos(pos().x() + 75, pos().y()-24);
                bubble->setScale(2);
                scene()->addItem(bubble);

                // ����һ����ʱ����������ʾһ��ʱ���ɾ��
                QTimer::singleShot(1000, [bubble]() { if(startpage::closeWinTellItem)delete bubble; });
                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/FumeShroom/idle.gif");
        }
    }
}

bool FumeShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 200 && pos().y() == other->pos().y() && other->pos().x() > pos().x();
}
