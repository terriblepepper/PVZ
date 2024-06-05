#include "smallBubble.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>
smallBubble::smallBubble(int attack, bool flag)
{
	atk = attack; // 设置攻击力
	speed = 230.0 * (33333 / fpsIndex) / 1000000; // 设置小泡泡的速度
}

QRectF smallBubble::boundingRect() const
{
	// 边界矩形
	return QRectF(-12, -28, 24, 24); // 矩形的左上角坐标为(-12, -28)，宽度为24，高度为24
}

bool smallBubble::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	Q_UNUSED(mode)
		// 与僵尸碰撞时，返回true
		return other->type() == zombie::Type && qFuzzyCompare(other->y()+20, y()) && qAbs(other->x() - x()) < 15;
}

void smallBubble::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
		Q_UNUSED(widget)
		// 绘制小泡泡的图片
		painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(":/new/prefix1/smallBubble.gif"));
}

void smallBubble::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新绘制
    // 检测小泡泡与其他物体是否发生碰撞
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty())
    {
        // 当豌豆射手与僵尸碰撞时
        zombie* zom = qgraphicsitem_cast<zombie*>(items[qrand() % items.size()]);
        zom->hp -= atk; // 减少僵尸的生命值，受到豌豆射手的攻击
        delete this; // 删除豌豆射手对象
        return;
    }
    setX(x() + speed); // 更新位置，让其向前移动
    if (x()-originX > 280)
        delete this;
}
