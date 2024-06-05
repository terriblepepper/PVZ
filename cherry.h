#ifndef CHERRY_H
#define CHERRY_H

#include "plant.h"

class cherry : public QObject,public plant
{
    Q_OBJECT
public:
    cherry();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // CHERRY_H
