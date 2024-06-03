#pragma once
#include "zombie.h"
#include "plant.h"

class pyramidzombie : public zombie
{
public:
    pyramidzombie();
    void advance(int phase) override;
};