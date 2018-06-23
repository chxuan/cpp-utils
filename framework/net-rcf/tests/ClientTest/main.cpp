/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月10日 星期日 14时00分15秒
 ************************************************************************/

#include <iostream>
#include "RPCProtocolDefine.h"
#include "RCFClientWrapper.hpp"

int main()
{
    RCFClientWrapper<I_RPCMessageHandler> client("127.0.0.1", 50001);

    try
    {
        PeopleInfoMessage peopleInfo;
        int id = 1000;

        bool ok = client.rcfClientObject()->queryPeopleInfoByID(id, peopleInfo);
        if (ok)
        {
            std::cout << "name: " << peopleInfo.m_name << std::endl;
            std::cout << "age: " << peopleInfo.m_age << std::endl;
        }
        else
        {
            std::cout << "queryPeopleInfoByID failed" << std::endl;
        }
    }
    catch (const RCF::Exception& e)
    {
        std::cout << "Error: " << e.getErrorString() << std::endl;
    }

    return 0;
}

