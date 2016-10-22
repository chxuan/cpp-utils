#ifndef _THREAD_GUARD_H
#define _THREAD_GUARD_H

#include <thread>

class thread_guard
{
public:
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
    explicit thread_guard(std::thread& t) : _t(t) {}
    ~thread_guard()
    {
        if (_t.joinable())
        {
            _t.join();
        }
    }

private:
    std::thread& _t;
};

#endif
