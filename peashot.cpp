#include "peashot.h"
#include "zombie.h"
#include"gameIndex.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>

peashot::peashot(int attack, bool flag)
    : atk(attack), snow(flag), speed(360.0 * (33333 / fpsIndex) / 1000000)
{
    currentPixmap = QPixmap(snow ? ":/new/prefix1/PeaSnow.gif" : ":/new/prefix1/Pea.gif");
}


QRectF peashot::boundingRect() const
{
    // �����㶹���ֵı߽����
    return QRectF(-18, -42, 36, 36); 
}

bool peashot::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    // ���㶹�����뽩ʬ��ײʱ������true
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

void peashot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)
        painter->drawPixmap(QRect(-18, -42, 36, 36), currentPixmap);
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

void peashot::addAtk(double att)
{
    atk = atk + att;
}

void peashot::setImage(const QString& filePath)
{
    currentPixmap = QPixmap(filePath);
    update(); // ���»���
}
