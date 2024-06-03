#pragma once
#include "plant.h"

class Pot : public plant
{
public:
    Pot();
    void advance(int phase) override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
};