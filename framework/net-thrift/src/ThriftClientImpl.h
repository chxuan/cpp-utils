/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file ThriftClientImpl.h
* @brief thrift客户端通信实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-25
*/

#ifndef _THRIFTCLIENTIMPL_H
#define _THRIFTCLIENTIMPL_H

#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "RPCMessageService.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class Message;

#define CONNECT_MSEC_TIMEOUT        3000            // 默认连接超时时间，单位：毫秒
#define SEND_MSEC_TIMEOUT           10000           // 默认发送超时时间，单位：毫秒
#define RECIVED_MSEC_TIMEOUT        10000           // 默认接收超时时间，单位：毫秒

/**
* @brief thrift客户端实现类
*/
class ThriftClientImpl
{
public:
    ~ThriftClientImpl();

    /**
    * @brief init 初始化thrift客户端
    *
    * @param ip 服务器ip地址
    * @param port 服务器端口号，默认为9090
    */
    void init(const std::string& ip, unsigned int port = 9090);

    /**
    * @brief sendMessage 发送消息到服务器端
    *
    * @param message 发送的消息
    * @param retMessage 接收的消息
    *
    * @return 成功返回true，否则返回false
    */
    bool sendMessage(Message* message, Message* retMessage);

    /**
    * @brief deinit 反初始化，释放一些资源
    */
    void deinit();

    /**
    * @brief setConnectMsecTimeoutOnce 设置单次连接超时
    *
    * @param connectMsecTimeout 超时时间，单位：毫秒
    */
    void setConnectMsecTimeoutOnce(unsigned int connectMsecTimeout);

    /**
    * @brief setSendMsecTimeoutOnce 设置单次发送超时
    *
    * @param sendMsecTimeout 超时时间，单位：毫秒
    */
    void setSendMsecTimeoutOnce(unsigned int sendMsecTimeout);

    /**
    * @brief setRecivedMsecTimeoutOnce 设置单次接收超时
    *
    * @param recivedMsecTimeout 超时时间，单位：毫秒
    */
    void setRecivedMsecTimeoutOnce(unsigned int recivedMsecTimeout);

private:
    std::string m_ip;                                               ///< 服务器ip地址
    unsigned int m_port = 0;                                        ///< 服务器端口号
    unsigned int m_connectMsecTimeout = CONNECT_MSEC_TIMEOUT;       ///< 连接超时
    unsigned int m_sendMsecTimeout = SEND_MSEC_TIMEOUT;             ///< 发送超时
    unsigned int m_recivedMsecTimeout = RECIVED_MSEC_TIMEOUT;       ///< 接收超时
};

#endif
