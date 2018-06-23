/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年02月03日 星期三 15时06分27秒
 ************************************************************************/

#include <assert.h>
#include <iostream>
#include "TcpClientWrapper.h"
#include "PeopleInfoMessage.h"

class TcpClientMessageHandler
{
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
        std::cout << "Tcp client handle error: " << errorString << std::endl;
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
};

using TcpClientMessageHandlerPtr = std::shared_ptr<TcpClientMessageHandler>;

int main()
{
    TcpClientWrapperPtr client(new TcpClientWrapper("127.0.0.1", 8888));
    client->setThreadPoolNum(10);

    TcpClientMessageHandlerPtr handler(new TcpClientMessageHandler);

    ClientParam param;
    param.m_onRecivedMessage =
            std::bind(&TcpClientMessageHandler::handleReciveMessage,
                      handler, std::placeholders::_1, std::placeholders::_2);
    param.m_onHandleError =
            std::bind(&TcpClientMessageHandler::handleError,
                      handler, std::placeholders::_1, std::placeholders::_2);
    client->setClientParam(param);

    client->start();

    std::cout << "Client starting..." << std::endl;

    for (int i = 0; i < 10; ++i)
    //while (true)
    {
        PeopleInfoMessagePtr peopleInfoMessage(new PeopleInfoMessage);
        peopleInfoMessage->m_messageType = 1000;
        peopleInfoMessage->m_name = "Jack";
        peopleInfoMessage->m_age = 20;
        peopleInfoMessage->m_sex = 1;
        client->write(peopleInfoMessage);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::cout << "Client stoped..." << std::endl;

    return 0;
}
