#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <type_traits>

static const std::size_t max_thread_size = 100;

class thread_pool
{
public:
    using work_thread_ptr = std::shared_ptr<std::thread>;
    using task_t = std::function<void()>; 

    explicit thread_pool() : _is_stop_threadpool(false) {}

    ~thread_pool()
    {
        stop();
    }

    void init_thread_num(std::size_t num)
    {
        if (num <= 0 || num > max_thread_size)
        {
            std::string str = "Number of threads in the range of 1 to " + std::to_string(max_thread_size);
            throw std::invalid_argument(str);
        }

        for (std::size_t i = 0; i < num; ++i)
        {
            work_thread_ptr t = std::make_shared<std::thread>(std::bind(&thread_pool::run_task, this));
            _thread_vec.emplace_back(t);
        }
    }

    template<typename Function, typename... Args>
    void add_task(const Function& func, Args... args)
    {
        check_thread_status();
        task_t task = [&func, args...]{ return func(args...); };
        add_task_impl(task);
    }

    template<typename Function, typename... Args>
    typename std::enable_if<std::is_class<Function>::value>::type add_task(Function& func, Args... args)
    {
        check_thread_status();
        task_t task = [&func, args...]{ return func(args...); };
        add_task_impl(task);
    }

    template<typename Function, typename Self, typename... Args>
    void add_task(const Function& func, Self* self, Args... args)
    {
        check_thread_status();
        task_t task = [&func, &self, args...]{ return (*self.*func)(args...); };
        add_task_impl(task);
    }

    void stop()
    {
        std::call_once(_call_flag, [this]{ terminate_all(); });
    }

private:
    void add_task_impl(const task_t& task)
    {
        std::unique_lock<std::mutex> locker(_task_queue_mutex);
        _task_queue.emplace(std::move(task));
        _task_get.notify_one();
    }

    void terminate_all()
    {
        std::unique_lock<std::mutex> locker(_task_queue_mutex);

        _is_stop_threadpool = true;
        _task_get.notify_all();

        locker.unlock();

        for (auto& iter : _thread_vec)
        {
            if (iter != nullptr && iter->joinable())
            {
                iter->join();
            }
        }
        _thread_vec.clear();

        clean_task_queue();
    }

    void run_task()
    {
        while (true)
        {
            task_t task = nullptr;

            std::unique_lock<std::mutex> locker(_task_queue_mutex);

            while (_task_queue.empty() && !_is_stop_threadpool)
            {
                _task_get.wait(locker);
            }

            if (_is_stop_threadpool)
            {
                break;
            }

            if (!_task_queue.empty())
            {
                task = std::move(_task_queue.front());
                _task_queue.pop();
            }

            locker.unlock();

            if (task != nullptr)
            {
                task();
            }
        }
    }

    void clean_task_queue()
    {
        while (!_task_queue.empty())
        {
            _task_queue.pop();
        }
    }

    void check_thread_status()
    {
        if (_is_stop_threadpool)
        {
            throw std::runtime_error("ThreadPool is stoped");
        }
    }

private:
    std::vector<work_thread_ptr> _thread_vec;
    std::condition_variable _task_get;
    std::mutex _task_queue_mutex;
    std::queue<task_t> _task_queue;
    std::atomic<bool> _is_stop_threadpool;
    std::once_flag _call_flag;
};

#endif
