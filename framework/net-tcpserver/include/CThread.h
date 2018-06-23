/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CThread.h
* @brief 线程父类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#ifndef _CTHREAD_H
#define _CTHREAD_H

#include <assert.h>
#include <thread>
#include <memory>

/**
* @brief 线程类，封装了std::thread的常用函数
*/
class CThread
{
public:
    using ThreadPtr = std::shared_ptr<std::thread>;

    virtual ~CThread()
    {
        if (m_thread.use_count() != 0)
        {
            if (m_thread->joinable())
            {
                m_thread->join();
            }
        }
    }

    /**
    * @brief run 继承自CThread的类都要实现run函数
    */
    virtual void run() = 0;

public:
    /**
    * @brief start 启动线程是调用handleThread，handleThread再调用run函数
    */
    void start()
    {
        if (m_thread.use_count() == 0)
        {
            m_thread = std::make_shared<std::thread>(std::bind(&CThread::handleThread, this));
        }
    }

    bool joinable() const
    {
        assert(m_thread.use_count() != 0);
        return m_thread->joinable();
    }

    void join()
    {
        assert(m_thread.use_count() != 0);
        m_thread->join();
    }

    void detach()
    {
        assert(m_thread.use_count() != 0);
        m_thread->detach();
    }

    std::thread::id threadID() const
    {
        assert(m_thread.use_count() != 0);
        return m_thread->get_id();
    }

private:
    void handleThread()
    {
        run();
    }

private:
    ThreadPtr m_thread;
};

using CThreadPtr = std::shared_ptr<CThread>;

#endif
