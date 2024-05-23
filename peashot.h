#ifndef PEASHOT_H
#define PEASHOT_H
#include "other.h"
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
class peashot : public other
{
public:
    peashot(int attack = 0, bool flag = false); // ���캯��������һ���㶹����attack��ʾ��������flag��ʾ�Ƿ���б���Ч����Ĭ��Ϊ0��false
    QRectF boundingRect() const override; // �����㶹�ı߽���Σ�������ײ���
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override; // �ж��㶹�Ƿ�������ͼ�������ײ
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // �����㶹���ֵ����
    void advance(int phase) override; // �����㶹���ƶ��͹����߼�
private:
    bool snow; // ��־�Ƿ���б���Ч�����㶹
    int atk; // �㶹�Ĺ�����
    qreal speed; // �㶹���ٶȣ�ÿ���ƶ�����������
};

#endif // PEASHOT_H
