/************************************************
 * 该例程讲解用C++11来实现一个通用线程池
************************************************/
#include <iostream>
#include <string>
#include <chrono>
#include "ThreadPool.hpp"

void testTask(const std::string& str)
{
    std::cout << "Current thread id: " << std::this_thread::get_id() << ", str: " << str << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int main()
{
    ThreadPool pool;
    pool.initThreadNum(10);

    for (int i = 0; i < 10; ++i)
    {
        pool.addTask([]
        {
            std::cout << "Current thread id: " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
        pool.addTask(testTask, "Hello world");
    }

    std::cin.get();
    std::cout << "##############END###################" << std::endl;
    return 0;
}
