#include "smallBubble.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>
smallBubble::smallBubble(int attack, bool flag)
{
	atk = attack; // ���ù�����
	speed = 230.0 * (33333 / fpsIndex) / 1000000; // ����С���ݵ��ٶ�
}

QRectF smallBubble::boundingRect() const
{
	// �߽����
	return QRectF(-12, -28, 24, 24); // ���ε����Ͻ�����Ϊ(-12, -28)�����Ϊ24���߶�Ϊ24
}

bool smallBubble::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	Q_UNUSED(mode)
		// �뽩ʬ��ײʱ������true
		return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

void smallBubble::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
		Q_UNUSED(widget)
		// ����С���ݵ�ͼƬ
		painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(":/new/prefix1/smallBubble.gif"));
}

void smallBubble::advance(int phase)
{
    if (!phase)
        return;
    update(); // ���»���
    // ���С���������������Ƿ�����ײ
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        // ���㶹�����뽩ʬ��ײʱ
        zombie* zom = qgraphicsitem_cast<zombie*>(items[qrand() % items.size()]);
        zom->hp -= atk; // ���ٽ�ʬ������ֵ���ܵ��㶹���ֵĹ���
        delete this; // ɾ���㶹���ֶ���
        return;
    }
    setX(x() + speed); // ����λ�ã�������ǰ�ƶ�
    if (x()-originX > 280)
        delete this;
}
