#include <iostream>
#include "task_timer.h"

void test()
{
    std::cout << "Timer thread id: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    task_timer<> t0;
    t0.setSingleShot(true);
    t0.bind(test);
    t0.start(100);

    task_timer<> t;
    t.bind(test);
    t.bind([]{ std::cout << "Hello C++" << std::endl; });
    t.start(1000);

    std::cin.get();
    t.stop();
    std::cout << "Timer stop" << std::endl;

    std::cin.get();
    t.start();
    std::cout << "Timer restart" << std::endl;

    std::cin.get();
    t0.destroy();
    t.destroy();
    std::cout << "Timer destroy" << std::endl;

    std::cin.get();
    std::cout << "Process end" << std::endl;

    return 0;
}
