#ifndef CARD_H
#define CARD_H
#include "other.h"
#include<QString>

struct CardsData {
    QString name;//卡片名
    int cool; // 冷却时间
    int cost;      // 消耗阳光数
};

class card : public other
{
public:
    int counter;
    QString text;
    card(QString s);
    // 存储卡片原始数据
    static QMap<QString, CardsData> baseCardMap;  
    //存储所选取的卡片（name,cost,cool)
    static QMap<QString, CardsData>cardSelectedMap;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CARD_H
