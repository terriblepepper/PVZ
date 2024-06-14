#pragma once
#include "plant.h"

class PuffShroom : public plant
{
public:
    PuffShroom();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};