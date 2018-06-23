/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file TcpClientImpl.h
* @brief tcp客户端包装类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#include "TcpClientWrapper.h"

TcpClientWrapper::TcpClientWrapper(const std::string &ip, unsigned short port)
{
    m_impl.reset();
    if (m_impl.use_count() == 0)
    {
        m_impl = std::make_shared<TcpClientImpl>(ip, port);
    }
}

bool TcpClientWrapper::start()
{
    assert(m_impl.use_count() != 0);
    return m_impl->start();
}

bool TcpClientWrapper::stop()
{
    assert(m_impl.use_count() != 0);
    return m_impl->stop();
}

void TcpClientWrapper::setThreadPoolNum(unsigned int num)
{
    assert(m_impl.use_count() != 0);
    m_impl->setThreadPoolNum(num);
}

void TcpClientWrapper::setClientParam(const ClientParam &param)
{
    assert(m_impl.use_count() != 0);
    m_impl->setClientParam(param);
}
