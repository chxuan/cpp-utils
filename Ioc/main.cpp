#include <iostream>
#include "IocContainer.hpp"

class ICar
{
public:
    virtual ~ICar()
    {
        // Do nothing
    }

    virtual void test() = 0;
};

class Bus: public ICar
{
public:
    virtual void test() override
    {
        std::cout << "Bus::test" << std::endl;
    }
};

class Car : public ICar
{
public:
    virtual void test() override
    {
        std::cout << "Car::test" << std::endl;
    }
};

int main()
{
    IocContainer<ICar> ioc;
    ioc.registerType<Bus>("bus");
    ioc.registerType<Car>("car");

    std::shared_ptr<ICar> bus = ioc.resolveShared("bus");
    bus->test();
    std::shared_ptr<ICar> car = ioc.resolveShared("car");
    car->test();

    return 0;
}
