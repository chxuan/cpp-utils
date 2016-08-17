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

class Test
{
public:
    void print(const std::string& str, int i)
    {
        std::cout << "Test: " << str << ", i: " << i << std::endl;
    }
};

class Test2
{
public:
    void operator()(const std::string& str, int i)
    {
        std::cout << "Test2: " << str << ", i: " << i << std::endl;
    }
};

int main()
{
    Test t;
    Test2 t2;
    ThreadPool pool;
    pool.initThreadNum(10);

    std::string str = "Hello world";
    
    for (int i = 0; i < 1000; ++i)
    {
        pool.addTask([]{ std::cout << "Hello ThreadPool" << std::endl; });
        pool.addTask(testTask, str);
        pool.addTask(t2, str, i);
        pool.addTask(&Test::print, &t, str, i);
    }

    std::cin.get();
    std::cout << "##############END###################" << std::endl;
    return 0;
}
