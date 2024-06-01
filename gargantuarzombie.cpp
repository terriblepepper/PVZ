#include"gargantuarzombie.h"
#include"gameIndex.h"
#include<QDebug>
gargantuarzombie::gargantuarzombie()
{
    hp = 3000.0; 
    atk = 1500.0 * (33333.0 / (double)fpsIndex) / 1000000.0; 
    speed = 4.2 * (33333.0 / (double)fpsIndex) / 1000000.0;
    setMovie(":/new/prefix1/newZombies/gargantuar/walk_noimp.gif"); 
}

void gargantuarzombie::advance(int phase)
{
    if (!phase)
        return;
    update(); // ���»�����ʬ�Ļ���
    if (hp <= 0) // ���������ʬ������ֵС�ڵ���0����ʾ�Ѿ�������
    {
        if (state < 2) // ���������ʬ��״̬С��2����ʾ��������״̬
        {
            state = 2; // ��״̬����Ϊ2��������
            setMovie(":/new/prefix1/newZombies/gargantuar/death_noimp.gif");
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; 
        return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty()) // ���������ʬ������ͼ�������ײ
    {
        plant* pl = qgraphicsitem_cast<plant*>(items[0]);
        pl->hp -= atk; // ����ֲ�������ֵ���ܵ�������ʬ�Ĺ���
        qInfo() << "basicAtk" << atk;
        if (state != 1) // ���������ʬ��״̬��Ϊ1������״̬��
        {
            state = 1; // ��״̬����Ϊ1��������
            setMovie(":/new/prefix1/newZombies/gargantuar/smash_noimp.gif"); // ���û�����ʬ�Ĺ�������
        }
        return;
    }
    if (state) // ���������ʬ��״̬��Ϊ0������״̬��
    {
        state = 0; // ��״̬����Ϊ0�����ߣ�
        setMovie(":/new/prefix1/newZombies/gargantuar/walk_noimp.gif"); // ���û�����ʬ�����߶���
    }
    setX(x() - speed); // ���»�����ʬ��λ�ã����������ƶ�
}

void gargantuarzombie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QImage image = mQMovie->currentImage(); // ��ȡ��ǰ֡��ͼƬ

    if (isSnow && state != 3)
    {
        // ����֡ͼƬ�Ĳ������ص���ɫΪ��ɫ�����ڱ�ʾ��ʬ������״̬
        if (state != 2) // ���״̬��Ϊ2����ʬ��ͨ״̬��������֡�����ٶ�Ϊ50
            mQMovie->setSpeed(50);
        int w = image.width();
        int h = image.height();
        for (int i = 0; i < h; ++i)
        {
            uchar* line = image.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 200; // ��֡ͼƬ�����صĺ�ɫͨ������Ϊ200������Ϊ��ɫ
        }
    }

    // �ڻ����ϻ��ƽ�ʬ��֡ͼƬ
    painter->drawImage(QRectF(-140, -200, 280, 280), image); 
}

QRectF gargantuarzombie::boundingRect() const
{
    // ���ý�ʬ�ı߽����
    return QRectF(-160, -200, 400, 280);
}

