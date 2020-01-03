#pragma once

#include <mutex>
#include <condition_variable>

class count_down_latch
{
public:
    count_down_latch(int count) : count_(count) {}

    void count_down()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        --count_;
        if (count_ <= 0)
        {
            cond_.notify_one();
        }
    }

    void await()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        while (count_ > 0)
        {
            cond_.wait(lock);
        }
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    int count_;
};
