#include "PuffShroom.h"
#include"gameIndex.h"
#include"zombie.h"
#include"smallBubble.h"
PuffShroom::PuffShroom()
{
    hp = 250.0;
    atk = 15.0;
    time = int(1.6 * 1000000. / (33333. / (double)fpsIndex));
    setMovie(":/new/prefix1/newPlants/PuffShroom/idle.gif");
    setScale(1.3);
}

void PuffShroom::advance(int phase)
{
    if (!phase)
        return;
    update();
    if ((int)hp <= 0)
        delete this;
    else if (++counter >= time) // ÿ��һ�����������֡��
    {
        counter = 0; // ���ü�����
        if (!collidingItems().isEmpty())
        {
            setMovie(":/new/prefix1/newPlants/PuffShroom/shooting.gif");
            smallBubble* newshot = new smallBubble(atk); 
            newshot->originX = x() + 15;
            newshot->setX(newshot->originX); 
            newshot->setY(y()); // �����ӵ��ĸ߶���С�繽��ͬ
            scene()->addItem(newshot); // ��������ӵ�������
            return; // ���أ��������ƶ�
        }
        else
        {
            setMovie(":/new/prefix1/newPlants/PuffShroom/idle.gif");
        }
    }
}

bool PuffShroom::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
        return other->type() == zombie::Type && qAbs(pos().x() - other->pos().x()) < 295 && pos().y() == other->pos().y() && other->pos().x() > pos().x();
}
