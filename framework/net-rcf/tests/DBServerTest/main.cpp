/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月09日 星期六 20时26分44秒
 ************************************************************************/

#include <iostream>
#include "RPCProtocolDefine.h"
#include "RCFServerWrapper.hpp"

class RCFMessageHandler
{
public:
    bool queryPeopleInfoByID(int id, PeopleInfoMessage& peopleInfo)
    {
        if (id == 1000)
        {
            peopleInfo.m_name = "Jack";
            peopleInfo.m_age = 24;
            
            return true;
        }

        return false;
    }
};

int main()
{
    RCFMessageHandler rcfMessageHandler;
    RCFServerWrapper<I_RPCMessageHandler> server(50002);

    bool ok = server.start(rcfMessageHandler);
    if (ok)
    {
        std::cout << "DB server start..." << std::endl;
    }
    else
    {
        std::cout << "DB server start failed" << std::endl;
        return -1;
    }

    std::cin.get();

    ok = server.stop();
    if (ok)
    {
        std::cout << "DB server stoped..." << std::endl;
    }
    else
    {
        std::cout << "DB server stoped failed" << std::endl;
    }

    return 0;
}

