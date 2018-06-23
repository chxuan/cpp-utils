/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CRealJob.cpp
* @brief 具体的任务类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-20
*/

#include "CRealJob.h"
#include <assert.h>

CRealJob::CRealJob(const OnDoTask& func, void* jobData)
    : CJob(),
      m_jobData(jobData)
{
    assert(func);
    m_doTask = func;
}

void CRealJob::run()
{
    if (m_doTask)
    {
        m_doTask(m_jobData);
    }
}
