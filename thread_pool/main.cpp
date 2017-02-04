#include <iostream>
#include <string>
#include <chrono>
#include "thread_pool.hpp"

void test_task(const std::string& str)
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

    try
    {
        thread_pool pool;
        pool.init_thread_num(10);

        std::string str = "Hello world";

        for (int i = 0; i < 1000; ++i)
        {
            pool.add_task([]{ std::cout << "Hello ThreadPool" << std::endl; });
            pool.add_task(test_task, str);
            pool.add_task(t2, str, i);
            pool.add_task(&Test::print, &t, str, i);
        }

        std::cin.get();
        std::cout << "##############END###################" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
