/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFSubscriberImpl.hpp
* @brief 订阅者实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-12
*/

#ifndef _RCFSUBSCRIBERIMPL_H
#define _RCFSUBSCRIBERIMPL_H

#include <RCF/RCF.hpp>
#include <assert.h>
#include <iostream>
#include <map>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

/**
* @brief 订阅参数
*/
class SubscriptionParam
{
public:
    SubscriptionParam()
        : m_port(0)
    {
        // Do nothing
    }

    std::string m_ip;               ///< 发布者的IP地址
    unsigned int m_port;            ///< 发布者的端口号
    std::string m_topicName;        ///< 订阅的主题 
};

/**
* @brief 订阅者实现类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFSubscriberImpl
{
public:
    typedef std::map<std::string, RCF::SubscriptionPtr> RcfSubscriptionMap;

    RCFSubscriberImpl()
    {
        m_rcfInit.reset();
        m_rcfServer.reset();
    }

    ~RCFSubscriberImpl()
    {
        bool ok = stop();
        assert(ok);
    }

    /**
    * @brief start 开启服务器
    *
    * @note 开启服务器之后，才能调用createSubscriber函数
    *
    * @return 成功返回true，否则返回false
    */
    bool start()
    {
        try
        {
            if (m_rcfInit == NULL)
            {
                m_rcfInit = boost::make_shared<RCF::RcfInitDeinit>();
            }

            if (m_rcfServer == NULL)
            {
                int port = -1;
                m_rcfServer = boost::make_shared<RCF::RcfServer>(RCF::TcpEndpoint(port));
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
    * @brief createSubscription 创建订阅
    *
    * @tparam RCFMessageHandler 类类型
    * @param rcfMessageHandler 消息处理对象
    * @param param 订阅者参数
    *
    * @note 调用该函数之前，请先调用start函数开启服务器
    *
    * @return 成功返回true，否则返回false
    */
    template<typename RCFMessageHandler>
    bool createSubscription(RCFMessageHandler& rcfMessageHandler, const SubscriptionParam& param)
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        if (isSubscriptionExists(param.m_topicName))
        {
            return false;
        }

        try
        {
            assert(m_rcfServer != NULL);
            RCF::SubscriptionParms subParms;
            subParms.setPublisherEndpoint(RCF::TcpEndpoint(param.m_ip, param.m_port));
            subParms.setTopicName(param.m_topicName);
            RCF::SubscriptionPtr rcfSubscription
                                = m_rcfServer->createSubscription<I_RCFMessageHandler>(rcfMessageHandler, subParms);
            m_rcfSubscriptionMap.insert(std::make_pair(param.m_topicName, rcfSubscription));
        }
        catch (const RCF::Exception& e)
        {
            std::cout << "Error: " << e.getErrorString() << std::endl;
            return false;
        }

        return true;
    }

    /**
    * @brief stop 停止订阅者服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool stop()
    {
        bool ok = closeAllSubscription();
        if (!ok)
        {
            return false;
        }

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
    * @brief closeSubscription 通过主题来停止订阅
    *
    * @param topicName 主题名称
    *
    * @return 成功返回true，否则返回false
    */
    bool closeSubscription(const std::string& topicName)
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        RcfSubscriptionMap::iterator iter = m_rcfSubscriptionMap.find(topicName);
        if (iter != m_rcfSubscriptionMap.end())
        {
            try
            {
                iter->second->close();
            }
            catch (const RCF::Exception& e)
            {
                std::cout << "Error: " << e.getErrorString() << std::endl;
                return false;
            }

            m_rcfSubscriptionMap.erase(iter);
            return true;
        }

        return false;
    }

    /**
    * @brief closeAllSubscription 停止所有的订阅
    *
    * @return 成功返回true，否则返回false
    */
    bool closeAllSubscription()
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        RcfSubscriptionMap::iterator begin = m_rcfSubscriptionMap.begin();
        RcfSubscriptionMap::iterator end = m_rcfSubscriptionMap.end();
        while (begin != end)
        {
            try
            {
                begin->second->close();
            }
            catch (const RCF::Exception& e)
            {
                std::cout << "Error: " << e.getErrorString() << std::endl;
                return false;
            }

            ++begin;
        }

        m_rcfSubscriptionMap.clear();
        return true;
    }

private:
    /**
    * @brief isSubscriptionExists 判断订阅是否存在
    *
    * @param topicName 主题名称
    *
    * @return 存在返回true，否则返回false
    */
    bool isSubscriptionExists(const std::string& topicName)
    {
        RcfSubscriptionMap::iterator iter = m_rcfSubscriptionMap.find(topicName);
        if (iter != m_rcfSubscriptionMap.end())
        {
            return true;
        }

        return false;
    }

private:
    typedef boost::shared_ptr<RCF::RcfInitDeinit> RcfInitDeinitPtr;
    RcfInitDeinitPtr m_rcfInit;              ///< RCF服务器初始化对象

    typedef boost::shared_ptr<RCF::RcfServer> RcfServerPtr;
    RcfServerPtr m_rcfServer;                ///< RCF服务器对象

    RcfSubscriptionMap m_rcfSubscriptionMap; ///< 订阅者map，key：主题名，value：订阅者
    boost::mutex m_mutex;                    ///< 订阅者map互斥锁
};

#endif
