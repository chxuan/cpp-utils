/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CWorkerThread.cpp
* @brief 工作线程类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#include "CWorkerThread.h"
#include "CThreadPool.h"
#include "CJob.h"

CWorkerThread::CWorkerThread()
    : CThread(),
      m_isStopWorkThread(false)
{
    // Do nothing
}

void CWorkerThread::run()
{
    while (true)
    {
        CJobPtr job;
        {
            std::unique_lock<std::mutex> locker(m_threadPool->m_jobQueueMutex);
            while (m_threadPool->m_jobQueue.empty() &&
                   !m_threadPool->m_isStopThreadPool &&
                   !m_isStopWorkThread)
            {
                m_threadPool->m_jobQueueGetCond.wait(locker);
            }

            if (m_threadPool->m_isStopThreadPool || m_isStopWorkThread)
            {
                break;
            }

            if (!m_threadPool->m_jobQueue.empty())
            {
                job = m_threadPool->m_jobQueue.front();
                m_threadPool->m_jobQueue.pop();
            }
        }

        if (job.use_count() != 0)
        {
            job->run();
            job.reset();
            m_threadPool->m_jobQueuePutCond.notify_one();
        }
    }
}

void CWorkerThread::setThreadPool(CThreadPoolPtr threadPool)
{
    assert(threadPool != NULL);
    m_threadPool = threadPool;
}

void CWorkerThread::stopWorkThread(bool isStopWorkThread)
{
    m_isStopWorkThread = isStopWorkThread;
}
