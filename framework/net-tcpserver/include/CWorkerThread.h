/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CWorkerThread.h
* @brief 工作线程类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#ifndef _CWORKERTHREAD_H
#define _CWORKERTHREAD_H

#include "CThread.h"
#include <atomic>

class CThreadPool;
class CJob;

using CThreadPoolPtr = std::shared_ptr<CThreadPool>;
using CJobPtr = std::shared_ptr<CJob>;

/**
* @brief 工作线程类，继承自CThread，执行具体的job
*/
class CWorkerThread
        : public CThread,
          public std::enable_shared_from_this<CWorkerThread>
{
public:
    CWorkerThread();

    /**
    * @brief run 实现run函数，在run函数里面等待并执行job
    */
    virtual void run();

public:
    /**
    * @brief setThreadPool 设置工作线程的线程池
    *
    * @param threadPool 线程池
    */
    void setThreadPool(CThreadPoolPtr threadPool);

    /**
    * @brief stopWorkThread 设置是否需要停止工作线程
    *
    * @param isStopWorkThread 是否停止工作线程的标志变量
    */
    void stopWorkThread(bool isStopWorkThread);

private:
    CThreadPoolPtr m_threadPool;
    std::atomic<bool> m_isStopWorkThread;
};

using CWorkerThreadPtr = std::shared_ptr<CWorkerThread>;

#endif
