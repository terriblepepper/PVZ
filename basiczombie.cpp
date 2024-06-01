#include "basiczombie.h"
#include"gameIndex.h"
#include<QDebug>
basiczombie::basiczombie()
{
    hp = 270.0; // ���û�����ʬ������ֵΪ270
    atk = 100.0 * (33333.0 / (double)fpsIndex) / 1000000.0; // ���û�����ʬ�Ĺ�����Ϊ100��ÿ�빥��100�㣩
    speed = 7.0 * (33333.0 / (double)fpsIndex) / 1000000.0; // ���û�����ʬ���ٶ�Ϊ5.0����/�루16����Ϊ֡�����
    setMovie(":/new/prefix1/ZombieWalk1.gif"); // ���û�����ʬ�����߶���
}

void basiczombie::advance(int phase)
{
    if (!phase)
        return;
    update(); // ���»�����ʬ�Ļ���
    if (hp <= 0) // ���������ʬ������ֵС�ڵ���0����ʾ�Ѿ�������
    {
        if (state < 2) // ���������ʬ��״̬С��2����ʾ��������״̬
        {
            state = 2; // ��״̬����Ϊ2��������
            setMovie(":/new/prefix1/ZombieDie.gif"); // ���û�����ʬ����������
            setHead(":/new/prefix1/ZombieHead.gif"); // ���û�����ʬ��ͷ�����䶯��
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; // ���������ʬ����������������ϣ�ɾ��������ʬ����
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()) // ���������ʬ������ͼ�������ײ
    {
        plant *pl = qgraphicsitem_cast<plant *>(items[0]);
        pl->hp -= atk; // ����ֲ�������ֵ���ܵ�������ʬ�Ĺ���
        qInfo() << "basicAtk" << atk;
        if (state != 1) // ���������ʬ��״̬��Ϊ1������״̬��
        {
            state = 1; // ��״̬����Ϊ1��������
            setMovie(":/new/prefix1/ZombieAttack.gif"); // ���û�����ʬ�Ĺ�������
        }
        return;
    }
    if (state) // ���������ʬ��״̬��Ϊ0������״̬��
    {
        state = 0; // ��״̬����Ϊ0�����ߣ�
        setMovie(":/new/prefix1/ZombieWalk1.gif"); // ���û�����ʬ�����߶���
    }
    setX(x() - speed); // ���»�����ʬ��λ�ã����������ƶ�
}
