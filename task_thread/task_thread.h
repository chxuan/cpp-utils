/**
 * @file task_thread.h
 * @brief 任务线程对象
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2018-01-02
 */
#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <functional>

class task_thread
{
public:
    task_thread(const std::function<void()>& func);
    ~task_thread();

    void stop();
    std::thread::id get_thread_id();

private:
    void task_func();
    task_thread(const task_thread&) = delete;
    task_thread& operator=(const task_thread&) = delete;

private:
    std::function<void()> func_;
    std::shared_ptr<std::thread> thread_;
    std::atomic<bool> active_{ true };
};
