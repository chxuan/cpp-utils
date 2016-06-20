/************************************************
 *该例程讲解用C++11实现AOP框架
************************************************/
#include <iostream>
#include "Aop.hpp"

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

void coreFunc(int n)
{
    std::cout << "invoke coreFunc: " << n << std::endl;
}

int main()
{
    aopInvoke<A, B>(&coreFunc, 100);
    return 0;
}
