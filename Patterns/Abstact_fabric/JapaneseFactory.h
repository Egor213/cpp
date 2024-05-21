#pragma once
#include "IFactory.h"
#include "JapaneseEngine.h"
#include "JapaneseCar.h"

class JapaneseFactory : public IFactory
{
public:
    IEngine* releaseEngine() override;
    ICar* releaseCar() override;
};