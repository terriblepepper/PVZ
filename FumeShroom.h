#pragma once
#include "plant.h"

class FumeShroom : public plant
{
public:
    FumeShroom();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};