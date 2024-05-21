#pragma once
#include "ICar.h"
#include "IEngine.h"

class IFactory
{
public:
    virtual IEngine* releaseEngine() = 0;
    virtual ICar* releaseCar() = 0;
};