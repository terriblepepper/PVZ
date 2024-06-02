#pragma once

#include "zombie.h"
#include "plant.h"

class yetizombie : public zombie
{
public:
    yetizombie();
    void advance(int phase) override;
};