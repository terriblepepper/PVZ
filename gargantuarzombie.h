#pragma once
#include "zombie.h"
#include "plant.h"

class gargantuarzombie : public zombie
{
public:
    gargantuarzombie();
    void advance(int phase) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    QRectF boundingRect()const override;
};