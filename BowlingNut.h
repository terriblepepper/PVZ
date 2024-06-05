#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include "plant.h"

class BowlingNut : public plant
{
public:
    BowlingNut(); // ���캯��������һ�����������attack��ʾ������
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override; // �ж��㶹�Ƿ�������ͼ�������ײ
    void advance(int phase) override; // ���Ʊ�������ƶ��͹����߼�
private:
    int atk; // ������
    qreal speed; // �ٶȣ�ÿ���ƶ�����������
};

