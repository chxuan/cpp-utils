/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFPublisherImpl.hpp
* @brief 发布者实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-12
*/

#ifndef _RCFPUBLISHERIMPL_H
#define _RCFPUBLISHERIMPL_H

#include <RCF/RCF.hpp>
#include <assert.h>
#include <iostream>
#include <map>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

/**
* @brief 发布者参数
*/
class PublisherParam
{
public:
    PublisherParam()
        : m_onSubscriberConnect(NULL),
        m_onSubscriberDisconnect(NULL)
    {
        // Do nothing
    }

    std::string m_topicName;                                 ///< 发布的主题
    RCF::OnSubscriberConnect m_onSubscriberConnect;          ///< 响应订阅者连接的函数
    RCF::OnSubscriberDisconnect m_onSubscriberDisconnect;    ///< 响应订阅者断开连接的函数
};

/**
* @brief 发布者实现类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFPublisherImpl
{
public:
    typedef typename boost::shared_ptr<RCF::Publisher<I_RCFMessageHandler> > RcfPublisherPtr;
    typedef typename std::map<std::string, RcfPublisherPtr > RcfPublisherMap;

    /**
    * @brief RCFPublisherImpl 构造函数
    *
    * @param port 发布的端口号
    */
    RCFPublisherImpl(unsigned int port)
        : m_port(port)
    {
        m_rcfInit.reset();
        m_rcfServer.reset();
    }

    ~RCFPublisherImpl()
    {
        bool ok = stop();
        assert(ok);
    }

    /**
    * @brief start 开启服务器
    *
    * @note 开启服务器之后，才能调用createPublisher函数
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
                m_rcfServer = boost::make_shared<RCF::RcfServer>(RCF::TcpEndpoint(m_port));
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
    * @brief createPublisher 通过主题来创建发布者
    *
    * @param param 发布者参数
    *
    * @note 调用该函数之前，请先调用start函数开启服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool createPublisher(const PublisherParam& param)
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        if (isPublisherExists(param.m_topicName))
        {
            return false;
        }

        try
        {
            assert(m_rcfServer != NULL);
            assert(param.m_onSubscriberConnect != NULL);
            assert(param.m_onSubscriberDisconnect != NULL);

            RCF::PublisherParms pubParms;
            pubParms.setTopicName(param.m_topicName);
            pubParms.setOnSubscriberConnect(param.m_onSubscriberConnect);
            pubParms.setOnSubscriberDisconnect(param.m_onSubscriberDisconnect);
            RcfPublisherPtr rcfPublisher = m_rcfServer->createPublisher<I_RCFMessageHandler>(pubParms);
            m_rcfPublisherMap.insert(std::make_pair(param.m_topicName, rcfPublisher));
        }
        catch (const RCF::Exception& e)
        {
            std::cout << "Error: " << e.getErrorString() << std::endl;
            return false;
        }

        return true;
    }

    /**
    * @brief stop 停止发布者服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool stop()
    {
        bool ok = closeAllPublisher();
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
    * @brief publishObject 通过主题名称得到发布者对象
    *
    * @param topicName 主题名称
    *
    * @return 成功返回发布和对象，失败返回NULL
    */
    RcfPublisherPtr rcfPublishObject(const std::string& topicName)
    {
        typename RcfPublisherMap::iterator iter = m_rcfPublisherMap.find(topicName);
        if (iter != m_rcfPublisherMap.end())
        {
            return iter->second;
        }

        return RcfPublisherPtr();
    }

    /**
    * @brief closePublisher 通过主题来停止发布者
    *
    * @param topicName 主题名称
    *
    * @return 成功返回true，否则返回false
    */
    bool closePublisher(const std::string& topicName)
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        typename RcfPublisherMap::iterator iter = m_rcfPublisherMap.find(topicName);
        if (iter != m_rcfPublisherMap.end())
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

            m_rcfPublisherMap.erase(iter);
            return true;
        }

        return false;
    }

    /**
    * @brief closeAllPublisher 停止所有的发布者
    *
    * @return 成功返回true，否则返回false
    */
    bool closeAllPublisher()
    {
        boost::lock_guard<boost::mutex> locker(m_mutex);

        typename RcfPublisherMap::iterator begin = m_rcfPublisherMap.begin();
        typename RcfPublisherMap::iterator end = m_rcfPublisherMap.end();
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

        m_rcfPublisherMap.clear();
        return true;
    }

private:
    /**
    * @brief isPublisherExists 判断发布者是否存在
    *
    * @param topicName 主题名称
    *
    * @return 存在返回true，否则返回false
    */
    bool isPublisherExists(const std::string& topicName)
    {
        typename RcfPublisherMap::const_iterator iter = m_rcfPublisherMap.find(topicName);
        if (iter != m_rcfPublisherMap.end())
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

    unsigned int m_port;                     ///< 发布的端口号
    RcfPublisherMap m_rcfPublisherMap;       ///< 发布者map，key：主题名，value：发布者
    boost::mutex m_mutex;                    ///< 发布者map互斥锁
};

#endif
