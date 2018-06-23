/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file CThreadPool.cpp
* @brief 线程池类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#include "CThreadPool.h"
#include "CWorkerThread.h"
#include "CJob.h"

static const unsigned int MaxJobQueueSize = 100000;
static const unsigned int MaxNumOfThread = 30;

CThreadPool::CThreadPool()
    : m_isStopThreadPool(false)
{
    // Do nothing
}

CThreadPool::~CThreadPool()
{
    terminateAll();
}

void CThreadPool::initThreadNum(unsigned int initNumOfThread)
{
    assert(initNumOfThread > 0 && initNumOfThread <= MaxNumOfThread);
    createIdleThread(initNumOfThread);
}

void CThreadPool::run(CJobPtr job)
{
    assert(job != NULL);

    if (m_isStopThreadPool)
    {
        return;
    }

    {
        std::unique_lock<std::mutex> locker(m_jobQueueMutex);
        while (m_jobQueue.size() == MaxJobQueueSize && !m_isStopThreadPool)
        {
            m_jobQueuePutCond.wait(locker);
        }

        m_jobQueue.push(job);
    }

    m_jobQueueGetCond.notify_one();
}

void CThreadPool::terminateAll()
{
    m_isStopThreadPool = true;
    m_jobQueueGetCond.notify_all();

    for (auto& iter : m_idleList)
    {
        if (iter->joinable())
        {
            iter->join();
        }
    }
    m_idleList.clear();

    cleanJobQueue();
}

void CThreadPool::createIdleThread(unsigned int num)
{
    for (unsigned int i = 0; i < num; ++i)
    {
        CWorkerThreadPtr idleThread(new CWorkerThread);
        idleThread->setThreadPool(shared_from_this());
        m_idleList.push_back(idleThread);
        idleThread->start();
    }
}

void CThreadPool::cleanJobQueue()
{
    std::lock_guard<std::mutex> locker(m_jobQueueMutex);
    while (!m_jobQueue.empty())
    {
        m_jobQueue.pop();
    }
}
