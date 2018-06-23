/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFClientImpl.h
* @brief RCF客户端通信框架实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-04
*/

#ifndef _RCFCLIENTIMPL_H
#define _RCFCLIENTIMPL_H

#include <assert.h>
#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp>
#include <RCF/RCF.hpp>

#define MAX_CONNECT_TIMEOUTMS             (5*1000)          ///< 连接超时时间
#define MAX_REMOTE_CALL_TIMEOUTMS         (10*1000)         ///< 远程调用超时时间


/**
* @brief RCF客户端通信框架实现类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFClientImpl
{
public:
    typedef typename boost::shared_ptr<RcfClient<I_RCFMessageHandler> > RcfClientPtr;

    /**
    * @brief RCFClientImpl 构造函数
    *
    * @param ip 服务器ip地址
    * @param port 端口号
    */
    RCFClientImpl(const std::string& ip, unsigned int port)
        : m_ip(ip),
        m_port(port)
    {
        m_rcfInit.reset();
        m_rcfClient.reset();
        bool ok = init();
        assert(ok);

        setConnectTimeoutMs(MAX_CONNECT_TIMEOUTMS);
        setRemoteCallTimeoutMs(MAX_REMOTE_CALL_TIMEOUTMS);
    }

    /**
    * @brief rcfClientObject 得到RCF客户端对象
    *
    * @return 成功返回RCF客户端对象，失败返回NULL
    */
    RcfClientPtr rcfClientObject() const
    {
        assert(m_rcfClient != NULL);
        return m_rcfClient;
    }

    /**
    * @brief setConnectTimeoutMs 设置连接超时
    *
    * @param time 超时时间，单位为毫秒
    */
    void setConnectTimeoutMs(long long time)
    {
        assert(m_rcfClient != NULL);
        m_rcfClient->getClientStub().setConnectTimeoutMs(time);
    }

    /**
    * @brief setRemoteCallTimeoutMs 设置远程调用超时
    *
    * @param time 超时时间，单位为毫秒
    */
    void setRemoteCallTimeoutMs(long long time)
    {
        assert(m_rcfClient != NULL);
        m_rcfClient->getClientStub().setRemoteCallTimeoutMs(time);
    }

private:
    /**
    * @brief init 初始化客户端服务
    *
    * @return 成功返回true，否则返回false
    */
    bool init()
    {
        try
        {
            if (m_rcfInit == NULL)
            {
                m_rcfInit = boost::make_shared<RCF::RcfInitDeinit>();
            }

            if (m_rcfClient == NULL)
            {
                m_rcfClient = boost::make_shared<RcfClient<I_RCFMessageHandler> >(RCF::TcpEndpoint(m_ip, m_port));
            }
        }
        catch (const RCF::Exception& e)
        {
            std::cout << "Error: " << e.getErrorString() << std::endl;
            return false;
        }

        return true;
    }

private:
    typedef boost::shared_ptr<RCF::RcfInitDeinit> RcfInitDeinitPtr;
    RcfInitDeinitPtr m_rcfInit;                 ///< RCF客户端服务初始化对象

    RcfClientPtr m_rcfClient;                   ///< RCF客户端对象
    std::string m_ip;                           ///< 服务器ip地址
    unsigned int m_port;                        ///< 服务器端口号
};

#endif
