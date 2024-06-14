#pragma once
#include "plant.h"
#include "sun.h"

class SunShroom : public plant
{
public:
    SunShroom();
    void advance(int phase) override;
};