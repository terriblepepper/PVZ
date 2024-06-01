#pragma once
#include "plant.h"

class GatlingPea : public plant
{
public:
    GatlingPea();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};
