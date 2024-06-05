#pragma once
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include"puzzleMode.h"

class hammer : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 4 };
    hammer();
    int type() const override;
protected:
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
private:
    QPixmap normalPixmap;
    QPixmap clickedPixmap;
    double atk;
    bool enableAtk;//用于限制攻击速度
};