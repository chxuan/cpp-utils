#include <iostream>
#include "TaskCpp.hpp"

void testTask()
{
    taskcpp::Task<void()> task([]{ std::cout << "task" << std::endl; });
    task.wait();

    taskcpp::Task<int()> task2([]{ std::cout << "task2" << std::endl; return 2; });
    std::cout << "task2 ret: " << task2.get() << std::endl;

    taskcpp::Task<int(int)> task3([](int i){ std::cout << "task3" << std::endl; return i; });
    std::cout << "task3 ret: " << task3.get(3) << std::endl;
}

int main()
{
    testTask();
    return 0;
}

