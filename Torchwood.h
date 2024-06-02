#pragma once
#include "plant.h"

class Torchwood : public plant
{
public:
    Torchwood();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};