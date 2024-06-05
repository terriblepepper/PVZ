#ifndef POTATO_H
#define POTATO_H

#include "plant.h"

class potato : public QObject, public plant
{
    Q_OBJECT
public:
    potato();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // POTATO_H
