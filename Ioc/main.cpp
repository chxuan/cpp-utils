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

struct A
{
    void func()
    {
        std::cout << "A::func()" << std::endl;
    }
};

struct B
{
    void func()
    {
        std::cout << "B::func()" << std::endl;
    }
};
int main()
{
#if 0
    IocContainer<ICar> ioc;

    try
    {
        ioc.registerType<Bus>("bus");
        ioc.registerType<Car>("car");
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl; 
        return 1;
    }

    std::shared_ptr<ICar> bus = ioc.resolveShared("bus");
    bus->test();
    std::shared_ptr<ICar> car = ioc.resolveShared("car");
    car->test();
#endif
    IocContainer ioc;
    ioc.registerSimple<A>("a");
    ioc.registerSimple<B>("b");
    auto a = ioc.resolveShared<A>("a");
    a->func();
    auto b = ioc.resolveShared<B>("b");
    b->func();

    return 0;
}
