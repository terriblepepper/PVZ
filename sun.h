#ifndef SUN_H
#define SUN_H

#include "other.h"

class sun : public QObject,public other
{
    Q_OBJECT
public:
    sun();
    sun(QPointF pos);
    ~sun() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
private:
    QMovie *movie;
    QPointF dest;
    qreal speed;
    int counter;
    int time;
    bool iscollected;
};

#endif // SUN_H
