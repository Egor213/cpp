#include <iostream>
#include "RussianFactory.h"
#include "JapaneseFactory.h"

int main() {
    
    IFactory* jFactory = new JapaneseFactory();
    IEngine* jEngine = jFactory->releaseEngine();
    ICar* jCar = jFactory->releaseCar();

    jCar->createCar(jEngine);

    IFactory* rFactory = new RussianFactory();
    IEngine* rEngine = rFactory->releaseEngine();
    ICar* rCar = rFactory->releaseCar();

    rCar->createCar(rEngine);
    


    return 0;
}
