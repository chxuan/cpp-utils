#include "task_thread.h"

task_thread::task_thread(const std::function<void()>& func) 
    : func_(func)
{
    thread_ = std::make_shared<std::thread>(std::bind(&task_thread::task_func, this));
}

task_thread::~task_thread()
{
    stop();
}

void task_thread::stop()
{
    active_ = false;
    if (thread_->joinable())
    {
        thread_->join();
    }
}

std::thread::id task_thread::get_thread_id()
{
    return thread_->get_id();
}

void task_thread::task_func()
{
    while (active_)
    {
        func_();
    }
}
