#ifndef SNOWPEA_H
#define SNOWPEA_H

#include "plant.h"

class snowpea : public QObject, public plant
{
    Q_OBJECT
public:
    snowpea();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // SNOWPEA_H
