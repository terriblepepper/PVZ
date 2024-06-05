#pragma once

#include "plant.h"

class CaiWen : public QObject, public plant
{
    Q_OBJECT
public:
    CaiWen();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};