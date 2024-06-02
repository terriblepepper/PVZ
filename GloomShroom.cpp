#include "GloomShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"startpage.h"
#include<QTimer>
GloomShroom::GloomShroom()
{
    hp = 350.0;
    atk = 28.0;
    time = int(1.72 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/GloomShroom/idle.gif");
    setScale(2);
}

void GloomShroom::advance(int phase)
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
            setMovie(":/new/prefix1/newPlants/GloomShroom/shooting.gif");
            foreach(QGraphicsItem * item, items)
            {
                // �������ݶ���
                QGraphicsPixmapItem* bubbleUp = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleDown = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleLeft = new QGraphicsPixmapItem();
                QGraphicsPixmapItem* bubbleRight = new QGraphicsPixmapItem();

                QPixmap bubblePixmap(":/new/prefix1/Bubbles.gif");

                bubbleUp->setPixmap(bubblePixmap);
                bubbleDown->setPixmap(bubblePixmap);
                bubbleLeft->setPixmap(bubblePixmap);
                bubbleRight->setPixmap(bubblePixmap);

                QPointF pos = this->pos();

                // ��������λ��
                bubbleUp->setPos(pos.x(), pos.y() - 60); 
                bubbleDown->setPos(pos.x(), pos.y() + 60); 
                bubbleLeft->setPos(pos.x() - 130, pos.y()); 
                bubbleRight->setPos(pos.x() + 75, pos.y()); 

                // ��������ӵ�������
                scene()->addItem(bubbleUp);
                scene()->addItem(bubbleDown);
                scene()->addItem(bubbleLeft);
                scene()->addItem(bubbleRight);

                // ���ö�ʱ����������ʾһ��ʱ���ɾ��
                QTimer::singleShot(1000, [bubbleUp]() { if(startpage::closeWinTellItem)delete bubbleUp; });
                QTimer::singleShot(1000, [bubbleDown]() { if (startpage::closeWinTellItem)delete bubbleDown; });
                QTimer::singleShot(1000, [bubbleLeft]() { if (startpage::closeWinTellItem)delete bubbleLeft; });
                QTimer::singleShot(1000, [bubbleRight]() { if (startpage::closeWinTellItem)delete bubbleRight; });

                zombie* zom = qgraphicsitem_cast<zombie*>(item);
                zom->hp -= atk;
            }
        }
        else 
        {
            setMovie(":/new/prefix1/newPlants/GloomShroom/idle.gif");
        }
    }
}

bool GloomShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && QLineF(pos(), other->pos()).length() < 150;
}
