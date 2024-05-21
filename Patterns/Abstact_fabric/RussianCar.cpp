#include "RussianCar.h"


void RussianCar::createCar(IEngine* engine)
{
    std::cout << "Собрали Российский автомобиль: ";
    engine->createEngine();
}