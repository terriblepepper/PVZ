#ifndef CARD_H
#define CARD_H

#include "other.h"

class card : public other
{
public:
    int counter;
    QString text;
    card(QString s);
    static QMap<QString, int> map;
    static QVector<QString> name;
    static QVector<int> cost;
    static QVector<int> cool;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CARD_H
