/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年02月03日 星期三 15时06分27秒
 ************************************************************************/

#include <assert.h>
#include <iostream>
#include "TcpServerWrapper.h"
#include "PeopleInfoMessage.h"

class TcpServerMessageHandler
{
public:
    TcpServerMessageHandler(TcpServerWrapperPtr server)
    {
        assert(server.use_count() != 0);
        m_server = server;
    }

public:
    void handleReciveMessage(MessagePtr message, const std::string& remoteAddress)
    {
        std::cout << "remote address: " << remoteAddress << std::endl;
        unsigned int messageType = message->m_messageType;
        switch (messageType)
        {
        case 1000:
        {
            PeopleInfoMessagePtr peopleInfoMessage(new PeopleInfoMessage);
            bool ok = deSerialize(message, peopleInfoMessage);
            assert(ok);

            std::cout << "#################" << std::endl;
            std::cout << "m_messageType: " << peopleInfoMessage->m_messageType << std::endl;
            std::cout << "m_name: " << peopleInfoMessage->m_name << std::endl;
            std::cout << "m_age: " << peopleInfoMessage->m_age << std::endl;
            std::cout << "m_sex: " << peopleInfoMessage->m_sex << std::endl;
            std::cout << "#################" << std::endl;

            PeopleInfoMessagePtr peopleInfo(new PeopleInfoMessage);
            peopleInfo->m_messageType = 1000;
            peopleInfo->m_name = "Jack";
            peopleInfo->m_age = 20;
            peopleInfo->m_sex = 1;
            m_server->write(peopleInfo, remoteAddress);

            break;
        }
        default:
        {
            std::cout << "Unknown message type: " << messageType << std::endl;
            break;
        }
        }
    }

    void handleError(const std::string& errorString, const std::string& remoteAddress)
    {
        (void)remoteAddress;
        std::cout << "Tcp server handle error: " << errorString << std::endl;
    }

    void handleClientConnect(const std::string& remoteAddress)
    {
        std::cout << "Client connected, remote address: " << remoteAddress << std::endl;
    }

    void handleClientDisconnect(const std::string& remoteAddress)
    {
        std::cout << "Client disconnected, remote address: " << remoteAddress << std::endl;
    }

private:
    template<typename T>
    bool deSerialize(const MessagePtr message, T t)
    {
        std::istringstream is(message->m_data);
        try
        {
            boost::archive::binary_iarchive ia(is);
            ia >> *t;
            t->m_messageType = message->m_messageType;
        }
        catch (std::exception& e)
        {
            std::cout << "DeSerialize data failed: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

private:
    TcpServerWrapperPtr m_server;
};

using TcpServerMessageHandlerPtr = std::shared_ptr<TcpServerMessageHandler>;

int main()
{
    TcpServerWrapperPtr server(new TcpServerWrapper(8888));
    server->setThreadPoolNum(10);

    TcpServerMessageHandlerPtr handler(new TcpServerMessageHandler(server));

    ServerParam param;
    param.m_onRecivedMessage =
            std::bind(&TcpServerMessageHandler::handleReciveMessage,
                      handler, std::placeholders::_1, std::placeholders::_2);
    param.m_onHandleError =
            std::bind(&TcpServerMessageHandler::handleError,
                      handler, std::placeholders::_1, std::placeholders::_2);
    param.m_onClientConnect =
            std::bind(&TcpServerMessageHandler::handleClientConnect,
                      handler, std::placeholders::_1);
    param.m_onClientDisconnect =
            std::bind(&TcpServerMessageHandler::handleClientDisconnect,
                      handler, std::placeholders::_1);
    server->setServerParam(param);

    bool ok = server->start();
    if (ok)
    {
        std::cout << "Server starting..." << std::endl;
    }
    else
    {
        std::cout << "Server start failed" << std::endl;
        return 0;
    }

    std::cin.get();

    std::cout << "Server stoped..." << std::endl;

    return 0;
}
