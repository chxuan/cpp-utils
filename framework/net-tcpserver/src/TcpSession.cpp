/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file TcpSession.cpp
* @brief tcp会话
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#include "TcpSession.h"

TcpSession::TcpSession(boost::asio::io_service& ioService)
    : m_socket(ioService)
{
    // Do nothing
}

void TcpSession::setTcpSessionParam(const TcpSessionParam& param)
{
    assert(param.m_onRecivedMessage);
    assert(param.m_onHandleError);
    m_onReciveMessage = param.m_onRecivedMessage;
    m_onHandleError = param.m_onHandleError;
}

boost::asio::ip::tcp::socket& TcpSession::socket()
{
    return m_socket;
}

std::string TcpSession::remoteIp()
{
    return m_socket.remote_endpoint().address().to_string();
}

unsigned short TcpSession::remotePort()
{
    return m_socket.remote_endpoint().port();
}

std::string TcpSession::remoteAddress()
{
    std::ostringstream os;
    os << remoteIp() << ":" << remotePort();
    return os.str();
}

void TcpSession::asyncRead()
{
    boost::asio::async_read(m_socket, boost::asio::buffer(m_inboundHeader),
                            boost::bind(&TcpSession::handleReadHeader, this,
                                        boost::asio::placeholders::error));
}

void TcpSession::handleReadHeader(const boost::system::error_code& error)
{
    if (error)
    {
        std::cout << "Read header failed: " << error.message() << std::endl;
        checkError(error);
        return;
    }

    Header header;
    memcpy(&header, m_inboundHeader, HeaderLength);

    m_inboundData.clear();
    m_inboundData.resize(header.m_dataSize);

    MessagePtr message(new Message);
    message->m_messageType = header.m_messageType;
    boost::asio::async_read(m_socket, boost::asio::buffer(m_inboundData),
                            boost::bind(&TcpSession::handleReadData, this,
                                        message, boost::asio::placeholders::error));
}

void TcpSession::handleReadData(MessagePtr message, const boost::system::error_code& error)
{
    asyncRead();

    if (error)
    {
        std::cout << "Read message data failed: " << error.message() << std::endl;
        checkError(error);
        return;
    }

    message->m_data = std::string(&m_inboundData[0], m_inboundData.size());
    if (m_onReciveMessage)
    {
        m_onReciveMessage(message, remoteAddress());
    }
}

void TcpSession::checkError(const boost::system::error_code& error)
{
    if (error)
    {
        if (m_onHandleError)
        {
            std::string errorString = error.message();
            if (errorString == "End of file")
            {
                m_onHandleError(errorString, remoteAddress());
            }
            else
            {
                m_onHandleError(errorString, "");
            }
        }
    }
}

