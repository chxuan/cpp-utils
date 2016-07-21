#include <iostream>
#include <thread>
#include <boost/timer.hpp>
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

void testTaskGroup()
{
    taskcpp::TaskGroup g;
    std::function<void()> f = []{ std::cout << "func" << std::endl; };
    auto f2 = []{ std::cout << "func2" << std::endl; };
    g.run(f);
    g.run(f2);
    g.run(f, f2, []{ std::cout << "func3" << std::endl; });

    taskcpp::Task<int()> task([]{ std::cout << "func4" << std::endl; return 2; });
    g.run(task);

    g.wait();
}

bool checkPrime(int x)
{
#if 0
    for (int i = 2; i < x; ++i)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
#endif
    int v = 1;
    for (int i = 1; i < 20; ++i)
    {
        v *= i;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return true;
}

void testParallelForeach()
{
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.emplace_back(i);
    }

    boost::timer t;
    /* std::for_each(vec.begin(), vec.end(), checkPrime); */
    taskcpp::parallelForeach(vec.begin(), vec.end(), checkPrime);
    std::cout << "for_each: " << t.elapsed() << std::endl;
}

int main()
{
    /* testTask(); */
    /* testTaskGroup(); */
    testParallelForeach();
    return 0;
}

