#include "active_thread.h"

active_thread::active_thread(const std::function<void()>& func) 
    : func_(func)
{
    thread_ = std::make_shared<std::thread>(std::bind(&active_thread::active_func, this));
}

active_thread::~active_thread()
{
    stop();
}

void active_thread::stop()
{
    active_ = false;
    if (thread_->joinable())
    {
        thread_->join();
    }
}

std::thread::id active_thread::get_thread_id()
{
    return thread_->get_id();
}

void active_thread::active_func()
{
    while (active_)
    {
        func_();
    }
}
