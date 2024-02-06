#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    virtual void setName(string* name) {}
    virtual string getName() const = 0;
    virtual Animal* clone() const = 0;
};


class Sheep : public Animal
{
private:
    string* name;
    Sheep(const Sheep& donor)
    {
        this->name = donor.name;
    }

public:
    Sheep() {}
    ~Sheep()
    {
        delete name;
    }

    void setName(string* name) override
    {
        this->name = name;
    }

    string getName() const override
    {
        return *name;
    }

    Sheep* clone() const override
    {
        return new Sheep(*this);
    }

};

int main()
{
    Sheep* sheepDonor = new Sheep();
    string name1 = "Oleg";
    string name2 = "Egor";
    sheepDonor->setName(&name1);
    Sheep* sheepClone = sheepDonor->clone();
    sheepClone->setName(&name2);
    std::cout << sheepDonor->getName() << '\n' << sheepClone->getName() << '\n';

    return 0;
}
