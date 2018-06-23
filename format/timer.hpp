#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

class timer
{
public:
    timer() : _begin(std::chrono::high_resolution_clock::now()) {}

    void reset()
    {
        _begin = std::chrono::high_resolution_clock::now();
    }

    // 默认输出毫秒.
    template<typename Duration = std::chrono::milliseconds>
    long long elapsed() const
    {
        return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - _begin).count();
    }

    // 微秒.
    long long elapsed_microseconds() const
    {
        return elapsed<std::chrono::microseconds>();
    }

    // 纳秒.
    long long elapsed_nanoseconds() const
    {
        return elapsed<std::chrono::nanoseconds>();
    }

    // 秒.
    long long elapsed_seconds() const
    {
        return elapsed<std::chrono::seconds>();
    }

    // 分.
    long long elapsed_minutes() const
    {
        return elapsed<std::chrono::minutes>();
    }

    // 时.
    long long elapsed_hours() const
    {
        return elapsed<std::chrono::hours>();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _begin;
};

#endif
