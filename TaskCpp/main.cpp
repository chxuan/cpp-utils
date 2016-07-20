#include <iostream>
#include "TaskCpp.hpp"
#include <thread>

void testTask()
{
    taskcpp::Task<void()> task([]{ std::cout << "task" << std::endl; });
    task.wait();

    taskcpp::Task<int()> task2([]{ std::cout << "task2" << std::endl; return 2; });
    std::cout << "task2 ret: " << task2.get() << std::endl;

    taskcpp::Task<int(int)> task3([](int i){ std::cout << "task3" << std::endl; return i; });
    std::cout << "task3 ret: " << task3.get(3) << std::endl;
}

void testTaskGroup()
{
    taskcpp::TaskGroup g;
    std::function<void()> f = []{ std::cout << "func" << std::endl; };
    auto f2 = []{ std::cout << "func2" << std::endl; };
    g.run(f);
    g.run(f2);
    g.run(f, f2, []{ std::cout << "func3" << std::endl; });
    g.wait();
}

int main()
{
    testTask();
    testTaskGroup();
    return 0;
}

