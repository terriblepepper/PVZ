#pragma once
#include "zombie.h"
#include "plant.h"

class apolozombie : public zombie
{
public:
    apolozombie();
    void advance(int phase) override;
};