/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月09日 星期六 20时26分44秒
 ************************************************************************/

#include <iostream>
#include "CenterNetServer.h"

int main()
{
    CenterNetServer server;
    bool ok = server.start();
    if (ok)
    {
        std::cout << "Center net server start..." << std::endl;
    }
    else
    {
        std::cout << "Center net server start failed" << std::endl;
        return -1;
    }

    std::cin.get();

    ok = server.stop();
    if (ok)
    {
        std::cout << "Center net server stoped..." << std::endl;
    }
    else
    {
        std::cout << "Center net server stoped failed" << std::endl;
        return -1;
    }

    return 0;
}

