#include <iostream>
#include "task_thread.h"

void print()
{
    std::cout << "hello world" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main()
{
    auto t = std::make_shared<task_thread>(std::bind(print));

    std::cin.get();
    /* t->stop(); */

    return 0;
}

