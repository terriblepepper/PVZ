#include "peashot.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>

peashot::peashot(int attack, bool flag)
{
    atk = attack; // �����㶹���ֵĹ�����
    snow = flag; // �����Ƿ���б���Ч���ı�־
    speed = 360.0 * (33333 / fpsIndex) / 1000000; // �����㶹���ֵ��ٶȣ�ÿ��360���أ�
}

QRectF peashot::boundingRect() const
{
    // �����㶹���ֵı߽����
    return QRectF(-12, -28, 24, 24); // ���ε����Ͻ�����Ϊ(-12, -28)�����Ϊ24���߶�Ϊ24
}

bool peashot::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    // ���㶹�����뽩ʬ��ײʱ������true
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

void peashot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // �����㶹���ֵ�ͼƬ�������Ƿ���б���Ч����ѡ��ͬ��ͼƬ
    painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/new/prefix1/PeaSnow.png" : ":/new/prefix1/Pea.png"));
}

void peashot::advance(int phase)
{
    if (!phase)
        return;
    update(); // �����㶹���ֵĻ���
    // ����㶹���������������Ƿ�����ײ
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        // ���㶹�����뽩ʬ��ײʱ
        zombie *zom = qgraphicsitem_cast<zombie *>(items[qrand() % items.size()]);
        zom->hp -= atk; // ���ٽ�ʬ������ֵ���ܵ��㶹���ֵĹ���

        // ����㶹���ִ��б���Ч�����ҽ�ʬû����
        if (snow && zom->isSnow==false)
        {
            zom->isSnow = true;
            zom->speed /= 2;
        } // ����ʬ���ٶȼ���Ϊԭ����1/2


        delete this; // ɾ���㶹���ֶ���
        return;
    }
    setX(x() + speed); // �����㶹���ֵ�λ�ã�������ǰ�ƶ�
    // ����㶹���ֵ�λ�ó�����Ļ�߽磨x > 1069������ɾ���㶹���ֶ���
    if (x() > 1069)
        delete this;
}