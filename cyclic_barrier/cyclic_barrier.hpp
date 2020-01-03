#pragma once

#include <mutex>
#include <condition_variable>

class cyclic_barrier
{
public:
    cyclic_barrier(int count) : count_(count) {}

    void await()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        --count_;

        while (count_ > 0)
        {
            cond_.wait(lock);
        }

        if (count_ <= 0)
        {
            cond_.notify_all();
        }
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    int count_;
};
