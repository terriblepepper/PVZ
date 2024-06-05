#pragma once
#include "plant.h"

class FumeShroom : public QObject , public plant
{
    Q_OBJECT
public:
    FumeShroom();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};