#pragma once
#include "plant.h"
#include "sun.h"

class SunShroom : public QObject, public plant
{
    Q_OBJECT
public:
    SunShroom();
    void advance(int phase) override;
};