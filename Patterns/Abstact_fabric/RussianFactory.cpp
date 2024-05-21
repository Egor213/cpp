#include "RussianFactory.h"

IEngine* RussianFactory::releaseEngine()
{
    return new RussianEngine();
}

ICar* RussianFactory::releaseCar()
{
    return new RussianCar();
}