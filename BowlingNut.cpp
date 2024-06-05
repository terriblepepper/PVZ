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
        // ���㶹�����뽩ʬ��ײʱ
        zombie* zom = qgraphicsitem_cast<zombie*>(items[qrand() % items.size()]);
        zom->hp -= atk; // ���ٽ�ʬ������ֵ
    }
    setX(x() + speed); // ����λ�ã�������ǰ�ƶ�
    // ���λ�ó�����Ļ�߽磨x > 1069������ɾ������
    if (x() > 1069)
        delete this;
}

