/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月15日 星期日 20时46分11秒
 ************************************************************************/

#include <iostream>
#include <string>
#include "ThriftClientWrapper.h"
#include "ProtocolDef.h"
#include "Message.h"
#include "PeopleInfoMessage.h"

int main()
{
    ThriftClientWrapper client;
    client.init("127.0.0.1", 9090);

    QueryPeopleInfoMessage queryPeopleInfo;
    queryPeopleInfo.m_cardId = "1234567890";

    Message* message = new Message;
    message->m_messageType = PEOPLE_INFO_MSG;
    message->m_data = queryPeopleInfo.serializeSelf();

    Message* retMessage = new Message;

    client.sendMessage(message, retMessage);

    if (retMessage->m_messageType == PEOPLE_INFO_MSG)
    {
        PeopleInfoMessage peopleInfo;
        peopleInfo.deserializeSelf(retMessage->m_data);

        std::cout << "name: " << peopleInfo.m_name << std::endl;
        std::cout << "age: " << peopleInfo.m_age << std::endl;
        std::cout << "sex: " << peopleInfo.m_sex << std::endl;

        for (auto& cat : peopleInfo.m_cats)
        {
            std::cout << "cat name: " << cat.m_name << std::endl;
            std::cout << "cat age: " << cat.m_age << std::endl;
        }
    }

    if (retMessage != NULL)
    {
        delete retMessage;
        retMessage = NULL;
    }

    return 0;
}

