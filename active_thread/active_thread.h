#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <functional>

class active_thread
{
public:
    active_thread(const std::function<void()>& func);
    ~active_thread();

    void stop();
    std::thread::id get_thread_id();

private:
    void active_func();
    active_thread(const active_thread&) = delete;
    active_thread& operator=(const active_thread&) = delete;

private:
    std::function<void()> func_;
    std::shared_ptr<std::thread> thread_;
    std::atomic<bool> active_{ true };
};
