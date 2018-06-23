/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file TcpServerImpl.h
* @brief tcp服务器实现类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-31
*/

#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "TcpSession.h"

class CThreadManage;
using CThreadManagePtr = std::shared_ptr<CThreadManage>;

using OnClientConnect = std::function<void (const std::string&)>;
using OnClientDisconnect = std::function<void (const std::string&)>;

/**
 * @brief 服务器参数，设置接收消息、错误处理、客户端连接和断开连接回调函数
 */
struct ServerParam
{
    OnReciveMessage m_onRecivedMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;
    OnClientConnect m_onClientConnect = nullptr;
    OnClientDisconnect m_onClientDisconnect = nullptr;
};

/**
 * @brief tcp服务器实现类
 */
class TcpServerImpl
{
public:
    TcpServerImpl(unsigned short port);
    ~TcpServerImpl();

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
        TcpSessionPtr session = tcpSession(remoteAddress);
        if (session.use_count() != 0)
        {
            session->write(t);
        }
    }

private:
    /**
    * @brief bindAndListen 绑定并监听端口
    *
    * @return 成功返回true，否则返回false 
    */
    bool bindAndListen();

    /**
     * @brief accept 异步监听客户端的连接
     */
    void accept();

    /**
     * @brief handleAccept 处理客户端的连接
     *
     * @param tcpSession 服务器与客户端的会话
     * @param error 错误类型
     */
    void handleAccept(TcpSessionPtr tcpSession,
                      const boost::system::error_code& error);

    /**
     * @brief closeAllTcpSession 关闭服务器与所有的客户端的会话（连接）
     */
    void closeAllTcpSession();

    /**
     * @brief tcpSession 通过远端地址获得服务器与客户端的会话
     *
     * @param remoteAddress 远端地址
     *
     * @return tcp会话
     */
    TcpSessionPtr tcpSession(const std::string& remoteAddress);

    /**
     * @brief handleReciveMessage 处理接收到的消息
     *
     * @param message 消息
     * @param remoteAddress 远端地址
     */
    void handleReciveMessage(MessagePtr message, const std::string& remoteAddress);

    /**
     * @brief handleError 处理错误
     *
     * @param errorString 错误描述
     * @param remoteAddress 远端地址，该地址可能为空
     */
    void handleError(const std::string &errorString, const std::string& remoteAddress);

    /**
     * @brief closeTcpSession 通过远端地址关闭服务器与客户端的会话（连接）
     *
     * @param remoteAddress 远端地址
     *
     * @return 成功返回true，否则返回false
     */
    bool closeTcpSession(const std::string& remoteAddress);

private:
    unsigned short m_port = 0;
    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::acceptor m_acceptor;

    using ThreadPtr = std::shared_ptr<std::thread>;
    std::vector<ThreadPtr> m_ioServiceThreadVec;

    std::mutex m_sessionMapMutex;

    // key: ip:port(127.0.0.1:8888)
    using TcpSessionMap = std::unordered_map<std::string, TcpSessionPtr>;
    TcpSessionMap m_tcpSessionMap;

    CThreadManagePtr m_threadManage;

    OnReciveMessage m_onRecivedMessage = nullptr;
    OnHandleError m_onHandleError = nullptr;
    OnClientConnect m_onClientConnect = nullptr;
    OnClientDisconnect m_onClientDisconnect = nullptr;
};

using TcpServerImplPtr = std::shared_ptr<TcpServerImpl>;

#endif
