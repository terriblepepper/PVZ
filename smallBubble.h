#pragma once
#include "other.h"
class smallBubble : public other
{
public:
    smallBubble(int attack = 0, bool flag = false); // ���캯��������һ���㶹����attack��ʾ��������flag��ʾ�Ƿ���б���Ч����Ĭ��Ϊ0��false
    QRectF boundingRect() const override; // �����㶹�ı߽���Σ�������ײ���
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override; // �ж��㶹�Ƿ�������ͼ�������ײ
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override; // �����㶹���ֵ����
    void advance(int phase) override; // �����㶹���ƶ��͹����߼�
    int originX;//��ʼX����
private:
    double atk; // ������
    qreal speed; //�ƶ��ٶȣ�ÿ���ƶ�����������
};