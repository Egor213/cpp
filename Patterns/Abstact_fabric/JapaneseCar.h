#pragma once
#include "ICar.h"


class JapaneseCar : public ICar
{
public:
    void createCar(IEngine* engine) override;
};