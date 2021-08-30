/************************************************
 *该例程讲解用C++11实现AOP框架
************************************************/
#include <unistd.h>
#include <iostream>
#include "Aop.hpp"
#include "AopTimer.hpp"

class A
{
public:
    void before(int n)
    {
        std::cout << "before from A: " << n << std::endl;
    }

    void after(int n)
    {
        std::cout << "after from A: " << n << std::endl;
    }
};

class B
{
public:
    void before(int n)
    {
        std::cout << "before from B: " << n << std::endl;
    }

    void after(int n)
    {
        std::cout << "after from B: " << n << std::endl;
    }
};

class C
{
public:
    void before(int n)
    {
        std::cout << "before from C: " << n << std::endl;
    }

};

void coreFunc(int n)
{
    std::cout << "invoke coreFunc: " << n << std::endl;
}

void coreFunc2()
{
    usleep(2000 * 1000); 
}

int main()
{
    aopInvoke<A, B, C>(&coreFunc, 100);
    aopInvoke<AopTimer>(&coreFunc2);
    return 0;
}
