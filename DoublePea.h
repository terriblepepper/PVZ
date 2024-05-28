#ifndef REPEATER_H
#define REPEATER_H

#include "plant.h"
#include "zombie.h"
#include "peashot.h"

class DoublePea : public plant
{
public:
    DoublePea();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // REPEATER_H
