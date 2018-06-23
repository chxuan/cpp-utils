/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file TcpServerImpl.cpp
* @brief tcp服务器实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#include "TcpServerImpl.h"
#include "CThreadManage.h"
#include "CRealJob.h"
#include <unistd.h>
#include <iostream>

TcpServerImpl::TcpServerImpl(unsigned short port)
    : m_port(port),
      m_acceptor(m_ioService)
{
    // Do nothing
}

TcpServerImpl::~TcpServerImpl()
{
    stop();
}

bool TcpServerImpl::start()
{
    bool ok = bindAndListen();
    if (!ok)
    {
        return false;
    }

    accept();

    // 获取cpu数量
    unsigned int cpuNum = sysconf(_SC_NPROCESSORS_CONF);

    if (m_ioServiceThreadVec.size() == 0)
    {
        try
        {
            // 用线程池来run ioservice
            for (unsigned int i = 0; i < cpuNum; ++i)
            {
                ThreadPtr thread(new std::thread(boost::bind(&boost::asio::io_service::run, &m_ioService)));
                m_ioServiceThreadVec.push_back(thread);
            }
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    return true;
}

bool TcpServerImpl::stop()
{
    closeAllTcpSession();

    try
    {
        m_ioService.stop();
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    if (m_ioServiceThreadVec.size() != 0)
    {
        for (auto& iter : m_ioServiceThreadVec)
        {
            if (iter->joinable())
            {
                iter->join();
            }
        }
    }

    m_threadManage->terminateAll();

    return true;
}

void TcpServerImpl::setThreadPoolNum(unsigned int num)
{
    if (m_threadManage.use_count() == 0)
    {
        m_threadManage = std::make_shared<CThreadManage>();
        m_threadManage->initThreadNum(num);
    }
}

void TcpServerImpl::setServerParam(const ServerParam &param)
{
    assert(param.m_onRecivedMessage);
    assert(param.m_onHandleError);
    assert(param.m_onClientConnect);
    assert(param.m_onClientDisconnect);

    m_onRecivedMessage = param.m_onRecivedMessage;
    m_onHandleError = param.m_onHandleError;
    m_onClientConnect = param.m_onClientConnect;
    m_onClientDisconnect = param.m_onClientDisconnect;
}

bool TcpServerImpl::bindAndListen()
{
    try
    {
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), m_port);
        m_acceptor.open(ep.protocol());
        m_acceptor.bind(ep);
        m_acceptor.listen();
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void TcpServerImpl::accept()
{
    TcpSessionPtr tcpSession(new TcpSession(m_ioService));
    m_acceptor.async_accept(tcpSession->socket(),
        boost::bind(&TcpServerImpl::handleAccept, this, tcpSession,
                    boost::asio::placeholders::error));
}

void TcpServerImpl::handleAccept(TcpSessionPtr tcpSession,
                                 const boost::system::error_code &error)
{
    accept();

    if (!error)
    {
        TcpSessionParam tcpSessionParam;
        tcpSessionParam.m_onRecivedMessage = std::bind(&TcpServerImpl::handleReciveMessage,
                                                       this, std::placeholders::_1, std::placeholders::_2);
        tcpSessionParam.m_onHandleError = std::bind(&TcpServerImpl::handleError,
                                                    this, std::placeholders::_1, std::placeholders::_2);
        tcpSession->setTcpSessionParam(tcpSessionParam);

        std::string remoteAddress = tcpSession->remoteAddress();
        {
            std::lock_guard<std::mutex> locker(m_sessionMapMutex);
            m_tcpSessionMap.insert(std::make_pair(remoteAddress, tcpSession));
        }
        if (m_onClientConnect != nullptr)
        {
            m_onClientConnect(remoteAddress);
        }

        tcpSession->asyncRead();
    }
    else
    {
        std::cout << "Tcp server accept failed: " << error.message() << std::endl;
        if (m_onHandleError != nullptr)
        {
            m_onHandleError(error.message(), "");
        }
    }
}

void TcpServerImpl::closeAllTcpSession()
{
    std::lock_guard<std::mutex> locker(m_sessionMapMutex);
    auto begin = m_tcpSessionMap.begin();
    auto end = m_tcpSessionMap.end();
    while (begin != end)
    {
        TcpSessionPtr session = begin->second;
        try
        {
            session->socket().close();
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }

        ++begin;
    }

    m_tcpSessionMap.clear();
}

TcpSessionPtr TcpServerImpl::tcpSession(const std::string& remoteAddress)
{
    std::lock_guard<std::mutex> locker(m_sessionMapMutex);
    auto iter = m_tcpSessionMap.find(remoteAddress);
    if (iter != m_tcpSessionMap.end())
    {
        return iter->second;
    }

    return TcpSessionPtr();
}

void TcpServerImpl::handleReciveMessage(MessagePtr message, const std::string& remoteAddress)
{
    if (message.use_count() == 0)
    {
        std::cout << "Tcp server message.use_count() == 0" << std::endl;
        return;
    }

    CRealJobPtr job(new CRealJob(m_onRecivedMessage, message, remoteAddress));
    m_threadManage->run(job);
}

void TcpServerImpl::handleError(const std::string &errorString, const std::string &remoteAddress)
{
    if (errorString == "End of file")
    {
        closeTcpSession(remoteAddress);
        if (m_onClientDisconnect != nullptr)
        {
            m_onClientDisconnect(remoteAddress);
        }
    }
    else
    {
        if (m_onHandleError != nullptr)
        {
            m_onHandleError(errorString, remoteAddress);
        }
    }
}

bool TcpServerImpl::closeTcpSession(const std::string &remoteAddress)
{
    std::lock_guard<std::mutex> locker(m_sessionMapMutex);
    auto iter = m_tcpSessionMap.find(remoteAddress);
    if (iter != m_tcpSessionMap.end())
    {
        TcpSessionPtr session = iter->second;
        try
        {
            session->socket().close();
            m_tcpSessionMap.erase(iter);
            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            m_tcpSessionMap.erase(iter);
            return false;
        }
    }

    return false;
}
