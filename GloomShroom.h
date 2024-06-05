#pragma once
#include "plant.h"

class GloomShroom : public QObject, public plant
{
    Q_OBJECT
public:
    GloomShroom();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};