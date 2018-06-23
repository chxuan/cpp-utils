/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file TcpServerImpl.h
* @brief tcp服务器包装类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#ifndef _TCPSERVERWRAPPER_H
#define _TCPSERVERWRAPPER_H

#include "TcpServerImpl.h"

/**
* @brief tcp服务器包装类
*/
class TcpServerWrapper
{
public:
    TcpServerWrapper(unsigned short port);

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
    * @brief setClientParam 设置服务器参数，主要是回调函数
    *
    * @param param 服务器参数
    */
    void setServerParam(const ServerParam& param);

    /**
    * @brief write 同步写数据
    *
    * @tparam T 模版类型
    * @param t 消息结构
    * @param remoteAddress 客户端地址（地址格式：127.0.0.1:8888）
    */
    template<typename T>
    void write(const T& t, const std::string& remoteAddress)
    {
        assert(m_impl.use_count() != 0);
        m_impl->write(t, remoteAddress);
    }

private:
    TcpServerImplPtr m_impl;
};

using TcpServerWrapperPtr = std::shared_ptr<TcpServerWrapper>;

#endif
