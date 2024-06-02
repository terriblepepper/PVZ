#pragma once
#include "plant.h"
#include "sun.h"

class TwinSunflower : public plant
{
public:
    TwinSunflower();
    void advance(int phase) override;
};