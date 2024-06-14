#pragma once
#include "plant.h"

class Jalapeno : public plant
{
public:
    Jalapeno();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};
