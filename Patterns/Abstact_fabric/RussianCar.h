#pragma once
#include "ICar.h"


class RussianCar : public ICar
{
public:
    void createCar(IEngine* engine) override;
};