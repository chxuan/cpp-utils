/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file RCFPublisherWrapper.hpp
* @brief 发布者包装类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-12
*/

#ifndef _RCFPUBLISHERWRAPPER_H
#define _RCFPUBLISHERWRAPPER_H

#include "RCFPublisherImpl.hpp"

/**
* @brief 发布者包装类
*
* @tparam I_RCFMessageHandler 类类型
*/
template<typename I_RCFMessageHandler>
class RCFPublisherWrapper
{
public:
    typedef boost::shared_ptr<RCF::Publisher<I_RCFMessageHandler> > RcfPublisherPtr;

    /**
    * @brief RCFPublisherWrapper 构造函数
    *
    * @param port 发布的端口号
    */
    RCFPublisherWrapper(unsigned int port)
    {
        m_impl.reset();
        if (m_impl == NULL)
        {
            m_impl = boost::make_shared<RCFPublisherImpl<I_RCFMessageHandler> >(port);
        }
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
        assert(m_impl != NULL);
        return m_impl->start();
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
        assert(m_impl != NULL);
        return m_impl->createPublisher(param);
    }

    /**
    * @brief stop 停止发布者服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool stop()
    {
        assert(m_impl != NULL);
        return m_impl->stop();
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
        assert(m_impl != NULL);
        RcfPublisherPtr publisher = m_impl->rcfPublishObject(topicName);
        assert(publisher != NULL);
        return publisher;
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
        assert(m_impl != NULL);
        return m_impl->closePublisher(topicName);
    }

    /**
    * @brief closeAllPublisher 停止所有的发布者
    *
    * @return 成功返回true，否则返回false
    */
    bool closeAllPublisher()
    {
        assert(m_impl != NULL);
        return m_impl->closeAllPublisher();
    }

private:
    typedef boost::shared_ptr<RCFPublisherImpl<I_RCFMessageHandler> > RCFPublisherImplPtr;
    RCFPublisherImplPtr m_impl;             ///< RCF发布者实现对象
};

#endif
