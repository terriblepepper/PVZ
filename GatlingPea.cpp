#include"GatlingPea.h"
#include "pea.h"
#include "zombie.h"
#include "peashot.h"
#include"gameIndex.h"

GatlingPea::GatlingPea()
{
    hp = 350.0; // �����㶹���ֵ�����ֵΪ200
    atk = 25.0; // �����㶹���ֵĹ�����Ϊ25
    time = int(1.4 * 1000000 / (33333 / fpsIndex)); // �����㶹���ֹ��������֡����1.4���Ӧ��֡����33333/fpsIndexΪ֡�����
    setMovie(":/new/prefix1/newPlants/GatlingPea/idle.gif"); // �����㶹���ֵĶ���
    setScale(2);
}

void GatlingPea::advance(int phase)
{
    if (!phase)
        return;
    update(); // �����㶹���ֵĻ���
    if ((int)hp <= 0)
        delete this; // ����㶹���ֵ�����ֵС�ڵ���0��ɾ���㶹���ֶ���
    else if (++counter >= time) // ÿ��һ�����������֡��
    {
        counter = 0; // ���ü�����
        // ����㶹����������ͼ�������ײ������ʬ���㶹���ֵĹ�����Χ�ڣ�
        if (!collidingItems().isEmpty())
        {
            peashot* pe = new peashot(atk);
            pe->setX(x() + 30);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 60);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 90);
            pe->setY(y());
            scene()->addItem(pe);
            pe = new peashot(atk);
            pe->setX(x() + 120);
            pe->setY(y());
            scene()->addItem(pe);
            return;
        }
    }
}

bool GatlingPea::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        // ���㶹�����뽩ʬ��ͬһ�������ϣ�y��ȣ�������ײʱ������true
        return other->type() == zombie::Type && qFuzzyCompare(other->y(), y());
}
