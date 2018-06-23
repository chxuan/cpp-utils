/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file TcpSession.h
* @brief tcp会话类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#ifndef _TCPSESSION_H
#define _TCPSESSION_H

#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Message.h"

using OnReciveMessage = std::function<void (MessagePtr, const std::string&)>;
using OnHandleError = std::function<void (const std::string&, const std::string&)>;

/**
* @brief 会话参数，设置接收消息、错误处理回调函数
*/
struct TcpSessionParam
{
    OnReciveMessage m_onRecivedMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;
};

/**
* @brief 消息头部，包含消息体大小、消息类型
*/
struct Header
{
    unsigned int m_dataSize = 0;
    unsigned int m_messageType = 0;
};

/**
* @brief tcp会话类，提供服务器与客户端的通信接口
*/
class TcpSession
{
public:
    TcpSession(boost::asio::io_service& ioService);

    /**
    * @brief setTcpSessionParam 设置会话参数
    *
    * @param param 会话参数
    */
    void setTcpSessionParam(const TcpSessionParam& param);

    /**
    * @brief socket 获取socket
    *
    * @return socket
    */
    boost::asio::ip::tcp::socket& socket();

    /**
    * @brief remoteIp 获取ip地址
    *
    * @return ip地址
    */
    std::string remoteIp();

    /**
    * @brief remotePort 获取端口号
    *
    * @return 端口号
    */
    unsigned short remotePort();

    /**
    * @brief remoteAddress 获取远端地址（地址格式：127.0.0.1:8888）
    *
    * @return 远端地址
    */
    std::string remoteAddress();

    /**
    * @brief asyncRead 异步读取消息
    */
    void asyncRead();

    /**
    * @brief write 同步写消息
    *
    * @tparam T 摸板类型
    * @param t 消息结构
    */
    template<typename T>
    void write(const T& t)
    {
        std::lock_guard<std::mutex> locker(m_writeMutex);

        // 序列化数据
        std::ostringstream archiveStream;
        try
        {
            boost::archive::binary_oarchive archive(archiveStream);
            archive << *t;
        }
        catch (std::exception& e)
        {
            std::cout << "Serialize data failed: " << e.what() << std::endl;
            return;
        }

        std::string messageData = archiveStream.str();

        Header header;
        header.m_dataSize = messageData.size();
        header.m_messageType = t->m_messageType;

        char headerBuf[HeaderLength] = {'\0'};
        memcpy(headerBuf, &header, sizeof(headerBuf));

        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(headerBuf));
        buffers.push_back(boost::asio::buffer(messageData));

        boost::system::error_code error;
        boost::asio::write(m_socket, buffers, error);
        checkError(error);
    }

private:
    /**
    * @brief handleReadHeader 处理读取的消息头
    *
    * @param error 错误类型
    */
    void handleReadHeader(const boost::system::error_code& error);

    /**
    * @brief handleReadData 处理读取的消息体
    *
    * @param message 消息
    * @param error 错误类型
    */
    void handleReadData(MessagePtr message, const boost::system::error_code& error);

    /**
    * @brief checkError 判断是什么类型的错误，然后做相应的处理
    *
    * @param error 错误类型
    */
    void checkError(const boost::system::error_code& error);

private:
    boost::asio::ip::tcp::socket m_socket;

    enum
    {
        HeaderLength = 8
    };

    char m_inboundHeader[HeaderLength];
    std::vector<char> m_inboundData;

    OnReciveMessage m_onReciveMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;

    std::mutex m_writeMutex;
};

using TcpSessionPtr = std::shared_ptr<TcpSession>;

#endif
