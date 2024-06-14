#pragma once
#include "zombie.h"
#include "plant.h"

class cleopatrazombie : public zombie
{
public:
    cleopatrazombie();
    void advance(int phase) override;
};