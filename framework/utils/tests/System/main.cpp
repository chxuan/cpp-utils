/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月29日 星期日 18时41分08秒
 ************************************************************************/

#include <iostream>
#include "Utils.h"

int main()
{
    std::cout << "####################uuid###################" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << utils::System::uuid() << std::endl;
    }

    std::cout << "########################md5##################" << std::endl;

    std::string str = "hello";
    std::cout << str << ": " << utils::System::md5(str) << std::endl;
    str = "中国";
    std::cout << str << ": " << utils::System::md5(str) << std::endl;

    std::cout << "####################sha1#####################" << std::endl;

    str = "hello";
    std::cout << str << ": " << utils::System::sha1(str) << std::endl;
    str = "中国";
    std::cout << str << ": " << utils::System::sha1(str) << std::endl;

    unsigned long totalram = utils::System::totalMemery();
    if (totalram != 0)
    {
        std::cout << "总内存大小：" << totalram / (1024 * 1024 * 1024 * 1.0) << "GB" << std::endl;
    }

    unsigned long freeram = utils::System::freeMemery();
    if (freeram != 0)
    {
        std::cout << "可用内存大小：" << freeram / (1024 * 1024 * 1024 * 1.0) << "GB" << std::endl;
    }

    return 0;
}
