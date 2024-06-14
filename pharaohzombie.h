#pragma once
#include "zombie.h"
#include "plant.h"

class pharaohzombie : public zombie
{
public:
    pharaohzombie();
    void advance(int phase) override;
};