#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <assert.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <type_traits>

static const unsigned int MaxTaskQueueSize = 100000;
static const unsigned int MaxNumOfThread = 30;

class ThreadPool
{
public:
    using WorkerThreadPtr = std::shared_ptr<std::thread>;
    using Task = std::function<void()>; 

    explicit ThreadPool() : m_isStopThreadPool(false) {}

    ~ThreadPool()
    {
        stop();
    }

    void initThreadNum(unsigned int num)
    {
        assert(num > 0 && num <= MaxNumOfThread);
        for (unsigned int i = 0; i < num; ++i)
        {
            WorkerThreadPtr t = std::make_shared<std::thread>(std::bind(&ThreadPool::runTask, this));
            m_threadVec.emplace_back(t);
        }
    }

    template<typename Function, typename... Args>
    void addTask(const Function& func, Args... args)
    {
        if (!m_isStopThreadPool)
        {
            Task task = [&func, args...]{ return func(args...); };
            addTaskImpl(task);
        }
    }

    template<typename Function, typename... Args>
    typename std::enable_if<std::is_class<Function>::value>::type addTask(Function& func, Args... args)
    {
        if (!m_isStopThreadPool)
        {
            Task task = [&func, args...]{ return func(args...); };
            addTaskImpl(task);
        }
    }

    template<typename Function, typename Self, typename... Args>
    void addTask(const Function& func, Self* self, Args... args)
    {
        if (!m_isStopThreadPool)
        {
            Task task = [&func, &self, args...]{ return (*self.*func)(args...); };
            addTaskImpl(task);
        }
    }

    void stop()
    {
        std::call_once(m_callFlag, [this]{ terminateAll(); });
    }

private:
    void addTaskImpl(const Task& task)
    {
        {
            std::unique_lock<std::mutex> locker(m_taskQueueMutex);
            while (m_taskQueue.size() == MaxTaskQueueSize && !m_isStopThreadPool)
            {
                m_taskPut.wait(locker);
            }

            m_taskQueue.emplace(std::move(task));
        }

        m_taskGet.notify_one();
    }

    void terminateAll()
    {
        m_isStopThreadPool = true;
        m_taskGet.notify_all();

        for (auto& iter : m_threadVec)
        {
            if (iter->joinable())
            {
                iter->join();
            }
        }
        m_threadVec.clear();

        cleanTaskQueue();
    }

    void runTask()
    {
        while (true)
        {
            Task task = nullptr;
            {
                std::unique_lock<std::mutex> locker(m_taskQueueMutex);
                while (m_taskQueue.empty() && !m_isStopThreadPool)
                {
                    m_taskGet.wait(locker);
                }

                if (m_isStopThreadPool)
                {
                    break;
                }

                if (!m_taskQueue.empty())
                {
                    task = std::move(m_taskQueue.front());
                    m_taskQueue.pop();
                }
            }

            if (task != nullptr)
            {
                task();
                m_taskPut.notify_one();
            }
        }
    }

    void cleanTaskQueue()
    {
        std::lock_guard<std::mutex> locker(m_taskQueueMutex);
        while (!m_taskQueue.empty())
        {
            m_taskQueue.pop();
        }
    }

private:
    std::vector<WorkerThreadPtr> m_threadVec;
    std::condition_variable m_taskPut;
    std::condition_variable m_taskGet;
    std::mutex m_taskQueueMutex;
    std::queue<Task> m_taskQueue;
    std::atomic<bool> m_isStopThreadPool;
    std::once_flag m_callFlag;
};

#endif
