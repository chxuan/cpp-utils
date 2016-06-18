/************************************************
 *该例程讲解用C++11实现一个计时器Timer
************************************************/
#include <unistd.h>
#include <iostream>
#include "Timer.hpp"

int main()
{
    Timer t; // 开始计时

    sleep(2);

    std::cout << "milliseconds: " << t.elapsed() << std::endl;
    std::cout << "microseconds: " << t.elapsedMicroseconds() << std::endl;
    std::cout << "nanoseconds: " << t.elapsedNanoSeconds() << std::endl;
    std::cout << "seconds: " << t.elapsedSeconds() << std::endl;
    std::cout << "minutes: " << t.elapsedMinutes() << std::endl;
    std::cout << "hours: " << t.elapsedHours() << std::endl;

    return 0;
}
