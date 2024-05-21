#include "JapaneseFactory.h"

IEngine* JapaneseFactory::releaseEngine()
{
    return new JapaneseEngine();
}

ICar* JapaneseFactory::releaseCar()
{
    return new JapaneseCar();
}