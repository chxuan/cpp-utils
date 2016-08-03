#include <iostream>
#include "ATimer.hpp"

void test()
{
    std::cout << "Timer thread id: " << std::this_thread::get_id() << std::endl;
}

void test2()
{
    std::cout << "Hello world" << std::endl;
}

int main()
{
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    ATimer<> t;
    t.bind(test);
    t.bind(std::bind(test2));
    t.bind([]{ std::cout << "Hello C++" << std::endl; });
    t.start(1000);

    std::cin.get();
    t.stop();
    std::cout << "Tiemr stop" << std::endl;

    std::cin.get();
    std::cout << "Process end" << std::endl;

    return 0;
}
