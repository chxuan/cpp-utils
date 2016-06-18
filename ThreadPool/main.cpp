/************************************************
 * 该例程讲解用C++11来实现一个通用线程池
************************************************/
#include <iostream>
#include <chrono>
#include "ThreadPool.hpp"

int main()
{
    ThreadPool pool;
    pool.initThreadNum(10);

    for (int i = 0; i < 1000; ++i)
    {
        pool.addTask([]
        {
            std::cout << "Current thread id: " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
    }

    std::cin.get();
    std::cout << "##############END###################" << std::endl;
    return 0;
}
