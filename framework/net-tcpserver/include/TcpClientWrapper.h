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

#ifndef _TCPCLIENTWRAPPER_H
#define _TCPCLIENTWRAPPER_H

#include "TcpClientImpl.h"

/**
* @brief tcp客户端包装
*/
class TcpClientWrapper
{
public:
    TcpClientWrapper(const std::string& ip, unsigned short port);

    /**
    * @brief start 开始服务
    *
    * @note 在调用该函数之前，请先调用setThreadPoolNum和setClientParam函数
    *
    * @return 成功返回true，否则返回false
    */
    bool start();

    /**
    * @brief stop 停止服务 
    *
    * @return 成功返回true，否则返回false
    */
    bool stop();

    /**
    * @brief setThreadPoolNum 设置线程池数量
    *
    * @param num 线程池数量
    */
    void setThreadPoolNum(unsigned int num);

    /**
    * @brief setClientParam 设置客户端参数，主要是回调函数
    *
    * @param param 客户端参数
    */
    void setClientParam(const ClientParam& param);

    /**
    * @brief write 同步写数据
    *
    * @param t 消息结构
    */
    template<typename T>
    void write(const T& t)
    {
        assert(m_impl.use_count() != 0);
        m_impl->write(t);
    }

private:
    TcpClientImplPtr m_impl;
};

using TcpClientWrapperPtr = std::shared_ptr<TcpClientWrapper>;

#endif
