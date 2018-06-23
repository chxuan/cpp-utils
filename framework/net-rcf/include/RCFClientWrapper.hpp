/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFClientWrapper.h
* @brief RCF客户端通信框架包装类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-04
*/

#ifndef _RCFCLIENTWRAPPER_H
#define _RCFCLIENTWRAPPER_H

#include "RCFClientImpl.hpp"

/**
* @brief RCf客户端通信框架包装类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFClientWrapper
{
public:
    typedef typename boost::shared_ptr<RcfClient<I_RCFMessageHandler> > RcfClientPtr;

    /**
    * @brief RCFClientWrapper 构造函数
    *
    * @param ip 服务器ip地址
    * @param port 端口号
    */
    RCFClientWrapper(const std::string& ip, unsigned int port)
    {
        m_impl.reset();
        if (m_impl == NULL)
        {
            m_impl = boost::make_shared<RCFClientImpl<I_RCFMessageHandler> >(ip, port);
        }
    }

    /**
    * @brief rcfClientObject 得到RCF客户端对象
    *
    * @return 成功返回RCF客户端对象，失败返回NULL
    */
    RcfClientPtr rcfClientObject() const
    {
        assert(m_impl != NULL);
        return m_impl->rcfClientObject();
    }

    /**
    * @brief setConnectTimeoutMs 设置连接超时
    *
    * @param time 超时时间，单位为毫秒
    */
    void setConnectTimeoutMs(long long time)
    {
        assert(m_impl != NULL);
        m_impl->setConnectTimeoutMs(time);
    }

    /**
    * @brief setRemoteCallTimeoutMs 设置远程调用超时
    *
    * @param time 超时时间，单位为毫秒
    */
    void setRemoteCallTimeoutMs(long long time)
    {
        assert(m_impl != NULL);
        m_impl->setRemoteCallTimeoutMs(time);
    }

private:
    typedef typename boost::shared_ptr<RCFClientImpl<I_RCFMessageHandler> > RCFClientImplPtr;
    RCFClientImplPtr m_impl;		///< RCF客户端实现类指针
};

#endif
