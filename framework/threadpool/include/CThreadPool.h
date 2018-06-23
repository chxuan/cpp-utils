/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CThreadPool.h
* @brief 线程池类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#ifndef _CTHREADPOOL_H
#define _CTHREADPOOL_H

#include "CThread.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class CWorkerThread;
class CJob;

using CWorkerThreadPtr = std::shared_ptr<CWorkerThread>;
using CJobPtr = std::shared_ptr<CJob>;

/**
* @brief 线程池类，管理并发线程
*/
class CThreadPool : public std::enable_shared_from_this<CThreadPool>
{
public:
    friend class CWorkerThread;

    CThreadPool();
    ~CThreadPool();

public:
    /**
    * @brief initThreadNum 初始化线程数量
    *
    * @param initNumOfThread 线程数量
    */
    void initThreadNum(unsigned int initNumOfThread);

    /**
    * @brief run 执行具体的job
    *
    * @param job 具体的任务
    */
    void run(CJobPtr job);

    /**
    * @brief terminateAll 终止全部的线程
    * 等待正在执行的线程执行完毕，等待执行的任务将不会再执行了
    */
    void terminateAll();

private:
    /**
    * @brief createIdleThread 创建空闲线程
    *
    * @param num 线程数量
    */
    void createIdleThread(unsigned int num);

    /**
    * @brief cleanJobQueue 清除任务队列
    */
    void cleanJobQueue();

private:
    std::vector<CWorkerThreadPtr> m_idleList;

    std::condition_variable_any m_jobQueuePutCond;
    std::condition_variable_any m_jobQueueGetCond;
    std::mutex m_jobQueueMutex;
    std::queue<CJobPtr> m_jobQueue;

    std::atomic<bool> m_isStopThreadPool;
};

using CThreadPoolPtr = std::shared_ptr<CThreadPool>;

#endif
