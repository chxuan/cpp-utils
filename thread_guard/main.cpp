#include <iostream>
#include "thread_guard.hpp"

void func()
{
    std::cout << "Hello std::thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main()
{
    std::thread t(func);
    thread_guard guard(t);
    return 0;
}
