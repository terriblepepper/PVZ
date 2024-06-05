#pragma once
#include "plant.h"

class Jalapeno : public QObject, public plant
{
    Q_OBJECT
public:
    Jalapeno();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};
