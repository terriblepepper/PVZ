#pragma once
#include "zombie.h"
#include "plant.h"

class flagzombie : public zombie
{
public:
    flagzombie();
    void advance(int phase) override;
};