#include "zombie.h"
#include "plant.h"
#include"gameIndex.h"
zombie::zombie()
{
    hp=atk=0.0;
    state = 0;
    speed=0.0;
    mQMovie=mhead=nullptr;
    isSnow = false;
}
zombie::~zombie()
{
    delete mQMovie;
    delete mhead;
}
QRectF zombie::boundingRect() const
{
    // ���ý�ʬ�ı߽����
    return QRectF(-80, -100, 200, 140); // ���ε����Ͻ�����Ϊ(-80, -100)�����Ϊ200���߶�Ϊ140
}

void zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QImage image = mQMovie->currentImage(); // ��ȡ��ǰ֡��ͼƬ

    // �����ʬ���ٶ�С��5.0 * (33333 / fpsIndex) / 1000000 ��״̬��Ϊ3����ʾ��ʬ�����٣�
    if (isSnow && state != 3)
    {
        // ����֡ͼƬ�Ĳ������ص���ɫΪ��ɫ�����ڱ�ʾ��ʬ������״̬
        if (state != 2) // ���״̬��Ϊ2����ʬ��ͨ״̬��������֡�����ٶ�Ϊ50
            mQMovie->setSpeed(50);
        int w = image.width();
        int h = image.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = image.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 200; // ��֡ͼƬ�����صĺ�ɫͨ������Ϊ200������Ϊ��ɫ
        }
    }

    // �ڻ����ϻ��ƽ�ʬ��֡ͼƬ
    painter->drawImage(QRectF(-70, -100, 140, 140), image); // ����λ��Ϊ(-70, -100)�����Ϊ140���߶�Ϊ140
    // ������ڽ�ʬ��ͷ������
    if (mhead)
    {
        image = mhead->currentImage(); // ��ȡͷ�������ĵ�ǰ֡ͼƬ
        // �����ʬ���ٶ�С��5.0 * (33333 / fpsIndex) / 1000000����ʾ��ʬ������
        if (isSnow)
        {
            int w = image.width();
            int h = image.height();

            for (int i = 0; i < h; ++i)
            {
                uchar *line = image.scanLine(i);
                for (int j = 5; j < w - 5; ++j)
                    line[j << 2] = 200; // ����֡ͼƬ�����صĺ�ɫͨ��Ϊ200������Ϊ��ɫ
            }
        }
        // �ڻ����ϻ��ƽ�ʬ��ͷ��֡ͼƬ
        painter->drawImage(QRectF(0, -100, 140, 140), image); // ����λ��Ϊ(0, -100)�����Ϊ140���߶�Ϊ140
    }
}

bool zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)

    // ����ʬ��ֲ����ײʱ������true
    return other->type() == plant::Type && qAbs(other->x() - x())<15 && qAbs(other->x() - x()) < 30;
}

void zombie::setMovie(QString path)
{
    if (mQMovie)
        delete mQMovie; // ɾ��ԭ�еĶ�������

    mQMovie = new QMovie(path); // �����µĶ�������
    mQMovie->start(); // ��������
}

void zombie::setHead(QString path)
{
    if (mhead)
        delete mhead; // ɾ��ԭ�е�ͷ����������

    mhead = new QMovie(path); // �����µ�ͷ����������
    mhead->start(); // ����ͷ������
}

int zombie::type() const
{
    return Type; // ���ؽ�ʬ������
}
