#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

class Timer
{
public:
    Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}

    void reset()
    {
        m_begin = std::chrono::high_resolution_clock::now();
    }

    // 默认输出毫秒.
    template<typename Duration = std::chrono::milliseconds>
    long long elapsed() const
    {
        return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    // 微秒.
    long long elapsedMicroseconds() const
    {
        return elapsed<std::chrono::microseconds>();
    }

    // 纳秒.
    long long elapsedNanoSeconds() const
    {
        return elapsed<std::chrono::nanoseconds>();
    }

    // 秒.
    long long elapsedSeconds() const
    {
        return elapsed<std::chrono::seconds>();
    }

    // 分.
    long long elapsedMinutes() const
    {
        return elapsed<std::chrono::minutes>();
    }

    // 时.
    long long elapsedHours() const
    {
        return elapsed<std::chrono::hours>();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

#endif
