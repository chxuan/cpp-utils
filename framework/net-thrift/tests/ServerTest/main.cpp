/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月15日 星期日 09时46分39秒
 ************************************************************************/

#include "ThriftServerWrapper.h"
#include "ProtocolDef.h"
#include "PeopleInfoMessage.h"
#include <iostream>
#include <vector>

static void messageTask(Message* message, Message* retMessage)
{
    if (message == NULL || retMessage == NULL)
    {
        std::cout << "message or retMessage is NULL" << std::endl;
        return;
    }

    std::cout << "Recived message type: " << message->m_messageType << std::endl;

    if (message->m_messageType == PEOPLE_INFO_MSG)
    {
        QueryPeopleInfoMessage queryPeopleInfo;
        queryPeopleInfo.deserializeSelf(message->m_data);

        if (queryPeopleInfo.m_cardId == "1234567890")
        {
            PeopleInfoMessage peopleInfo;
            peopleInfo.m_name = "Jack";
            peopleInfo.m_age = 20;
            peopleInfo.m_sex = 1;

            Cat cat1;
            cat1.m_name = "Tom";
            cat1.m_age = 1;
            
            Cat cat2;
            cat2.m_name = "John";
            cat2.m_age = 2;

            peopleInfo.m_cats.push_back(cat1);
            peopleInfo.m_cats.push_back(cat2);

            retMessage->m_data = peopleInfo.serializeSelf();
        }
    }
}

int main()
{
    ThriftServerWrapper server;
    server.setMessageCallback(messageTask);
    server.init(9090);
    server.start();

    std::cout << "Server start..." << std::endl;

    getchar();

    server.stop();
    server.deinit();

    std::cout << "Server stoped..." << std::endl;

    return 0;
}
