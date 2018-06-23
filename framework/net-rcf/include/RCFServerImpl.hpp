/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFServerImpl.hpp
* @brief RCF服务端通信框架实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-04
*/

#ifndef _RCFSERVERIMPL_H
#define _RCFSERVERIMPL_H

#include <RCF/RCF.hpp>
#include <assert.h>
#include <iostream>
#include <boost/smart_ptr.hpp>

#define MAX_THREAD_NUM 25    ///< 最大线程数量

/**
* @brief RCF服务端通信框架实现类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFServerImpl
{
public:
    /**
    * @brief RCFServerImpl 构造函数
    *
    * @param port 端口号
    */
    RCFServerImpl(unsigned int port)
        : m_port(port)
    {
        m_rcfInit.reset();
        m_rcfServer.reset();
    }

    ~RCFServerImpl()
    {
        bool ok = stop();
        assert(ok);
    }

    /**
    * @brief start 开启服务器
    *
    * @tparam RCFMessageHandler 类类型
    * @param rcfMessageHandler 消息处理对象
    *
    * @return 成功返回true，否则返回false
    */
    template<typename RCFMessageHandler>
    bool start(RCFMessageHandler& rcfMessageHandler)
    {
        try
        {
            if (m_rcfInit == NULL)
            {
                m_rcfInit = boost::make_shared<RCF::RcfInitDeinit>();
            }

            if (m_rcfServer == NULL)
            {
                m_rcfServer = boost::make_shared<RCF::RcfServer>(RCF::TcpEndpoint(m_port));
                m_rcfServer->bind<I_RCFMessageHandler>(rcfMessageHandler);
                RCF::ThreadPoolPtr threadPool(new RCF::ThreadPool(1, MAX_THREAD_NUM));
                m_rcfServer->setThreadPool(threadPool);
                m_rcfServer->start();
            }
        }
        catch (const RCF::Exception& e)
        {
            std::cout << "Error: " << e.getErrorString() << std::endl;
            return false;
        }

        return true;
    }

    /**
    * @brief stop 停止服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool stop()
    {
        try
        {
            assert(m_rcfServer != NULL);
            m_rcfServer->stop();    
        }
        catch (const RCF::Exception& e)
        {
            std::cout << "Error: " << e.getErrorString() << std::endl;
            return false;
        }

        return true;
    }

    /**
    * @brief clientAddress 获取客户端的ip地址和端口号
    *
    * @return 返回客户端的ip地址和端口号
    */
    std::string clientAddress() const
    {
        RCF::RcfSession& session = RCF::getCurrentRcfSession();
        const RCF::RemoteAddress& address = session.getClientAddress();
        return address.string();
    }

private:
    typedef boost::shared_ptr<RCF::RcfInitDeinit> RcfInitDeinitPtr;
    RcfInitDeinitPtr m_rcfInit;              ///< RCF服务器初始化对象

    typedef boost::shared_ptr<RCF::RcfServer> RcfServerPtr;
    RcfServerPtr m_rcfServer;                ///< RCF服务器对象

    unsigned int m_port;                     ///< 监听端口
};

#endif
