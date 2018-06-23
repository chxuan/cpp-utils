/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file ThriftServerImpl.h
* @brief thrift服务器实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-25
*/

#ifndef _THRIFTSERVERIMPL_H
#define _THRIFTSERVERIMPL_H

#include "RPCMessageService.h"
#include "ThriftServerWrapper.h"
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

/**
* @brief thrift服务器通信实现类
*/
class ThriftServerImpl
{
public:
    ~ThriftServerImpl();

    /**
    * @brief init 初始化thrift服务器端
    *
    * @param port 监听端口，默认为9090
    */
    void init(unsigned int port = 9090);

    /**
    * @brief start 开始服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool start();

    /**
    * @brief stop 停止服务器
    *
    * @return 成功返回true，否则返回false
    */
    bool stop();

    /**
    * @brief deinit 反初始化，释放一些资源
    */
    void deinit();

    /**
    * @brief setMessageCallback 设置消息回调函数
    *
    * @param func 回调函数指针
    */
    void setMessageCallback(MESSAGE_CALLBACK func);

private:
    /**
    * @brief serverStart 开始服务，该函数被线程调用
    *
    * @param server 自身指针
    */
    static void serverStart(ThriftServerImpl* server);

public:
    MESSAGE_CALLBACK m_messageCallback = nullptr;     ///< 消息回调函数

private:
    using TThreadedServerPtr = std::shared_ptr<TThreadedServer>;
    TThreadedServerPtr m_threadedServer;    ///< thrift服务

    using ThreadPtr = std::shared_ptr<std::thread>;
    ThreadPtr m_thread;                     ///< 启动服务的线程
    unsigned int m_port = 0;                ///< 监听端口
};

#endif
