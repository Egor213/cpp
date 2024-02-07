#pragma once
#include "IEngine.h"

class ICar
{
public:
    virtual void createCar(IEngine* engine) = 0;
};