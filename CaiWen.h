#pragma once

#include "plant.h"

class CaiWen : public plant
{
public:
    CaiWen();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};