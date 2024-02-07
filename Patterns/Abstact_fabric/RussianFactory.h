#pragma once
#include "IFactory.h"
#include "RussianEngine.h"
#include "RussianCar.h"

class RussianFactory : public IFactory
{
public:
    IEngine* releaseEngine() override;
    ICar* releaseCar() override;
};