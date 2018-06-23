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

CRealJob::CRealJob(const OnReciveMessage& func, MessagePtr message, const std::string& remoteAddress)
    : CJob(),
      m_message(message),
      m_remoteAddress(remoteAddress)
{
    assert(func);
    m_onReciveMessage = func;
}

CRealJob::~CRealJob()
{
    // Do nothing
}

void CRealJob::run()
{
    if (m_onReciveMessage != nullptr)
    {
        m_onReciveMessage(m_message, m_remoteAddress);
    }
}
