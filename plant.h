#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QPainter>

class plant : public QGraphicsItem
{
public:
    enum { Type = UserType + 1};
    double hp;
    int state;
    double atk;
    int counter;
    int time;
    bool isPot = false;
    QMovie* mQMovie;
    int type()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)override;
    void setMovie(QString path);
    QRectF boundingRect()const override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape)const override;
    plant();
    ~plant();
};

#endif // PLANT_H
