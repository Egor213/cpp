#include "JapaneseCar.h"


void JapaneseCar::createCar(IEngine* engine)
{
    std::cout << "Собрали японский автомобиль: ";
    engine->createEngine();
}