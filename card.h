#ifndef CARD_H
#define CARD_H
#include "other.h"
#include<QString>

struct CardsData {
    QString name;//��Ƭ��
    int cool; // ��ȴʱ��
    int cost;      // ����������
};

class card : public other
{
public:
    int counter;
    QString text;
    card(QString s);
    static QMap<QString, CardsData> baseCardMap;   // �洢��Ƭԭʼ����
    static QMap<QString, CardsData>cardSelectedMap;//�洢��ѡȡ�Ŀ�Ƭ��name,cost,cool)
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CARD_H
