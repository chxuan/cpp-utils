/************************************************
 * 该例程讲解用C++11来封装Linux下的信号注册函数
************************************************/
#include <iostream>
#include "Signal.hpp"

class A
{
public:
    void handleExit()
    {
        std::cout << "Process exit..." << std::endl;
        exit(0);
    }
};

int main()
{
    std::cout << "Process start..." << std::endl;
    A a;
    Signal::signal(SIGINT, std::bind(&A::handleExit, &a));
    std::cin.get();
    return 0;
}
