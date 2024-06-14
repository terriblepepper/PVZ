#pragma once
#include "zombie.h"
#include "plant.h"

class smallzombie : public zombie
{
public:
    smallzombie();
    void advance(int phase) override;
};