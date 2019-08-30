#pragma once

#include <list>
#include <mutex>
#include <condition_variable>

template<typename T>
class message_buffer
{
public:
    message_buffer() = default;
    message_buffer(std::size_t buffer_size) : buffer_size_(buffer_size) {}

    void reset(std::size_t buffer_size)
    {
        buffer_size_ = buffer_size;
    }

    void notify_one()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.notify_one();
    }

    void put(const T& message)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        buffer_.emplace_back(message);
        if (buffer_.size() >= buffer_size_)
        {
            cond_.notify_one();
        }
    }

    std::list<T> get()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        while (buffer_.empty())
        {
            cond_.wait(lock);
        }

        return std::move(buffer_);
    }

private:
    std::mutex mutex_;
    std::list<T> buffer_;
    std::condition_variable cond_;
    std::size_t buffer_size_ = 1;
};
