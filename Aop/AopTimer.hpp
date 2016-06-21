#ifndef _AOPTIMER_H
#define _AOPTIMER_H

#include <iostream>
#include <chrono>

class AopTimer
{
public:
    void before()
    {
        m_begin = std::chrono::high_resolution_clock::now();
    }

    void after()
    {
        long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() 
                                                                                 - m_begin).count();
        std::cout << "Used time: " << elapsed << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

#endif
