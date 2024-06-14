#pragma once

#include "zombie.h"
#include "plant.h"

class icetrackerzombie : public zombie
{
public:
    icetrackerzombie();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};