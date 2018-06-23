/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file TcpClientImpl.h
* @brief tcp客户端实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H

#include "TcpSession.h"

class CThreadManage;
using CThreadManagePtr = std::shared_ptr<CThreadManage>;

/**
* @brief 客户端参数，设置接收消息、错误处理回调函数
*/
struct ClientParam
{
    OnReciveMessage m_onRecivedMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;
};

class TcpClientImpl
{
public:
    TcpClientImpl(const std::string& ip, unsigned short port);
    ~TcpClientImpl();

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
        m_tcpSession.write(t);
    }

private:
    /**
    * @brief connect 异步连接服务器
    */
    void connect();

    /**
    * @brief handleConnect 处理连接结果
    *
    * @param error 错误类型
    */
    void handleConnect(const boost::system::error_code& error);

    /**
    * @brief handleReciveMessage 处理接收到的消息
    *
    * @param message 消息
    * @param remoteAddress 远端地址
    */
    void handleReciveMessage(MessagePtr message, const std::string& remoteAddress);

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::endpoint m_endpoint;

    using ThreadPtr = std::shared_ptr<std::thread>;
    std::vector<ThreadPtr> m_ioServiceThreadVec;

    TcpSession m_tcpSession;

    CThreadManagePtr m_threadManage;

    OnReciveMessage m_onRecivedMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;
};

using TcpClientImplPtr = std::shared_ptr<TcpClientImpl>;

#endif
