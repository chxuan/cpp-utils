/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月28日 星期六 17时52分52秒
 ************************************************************************/

#include <iostream>
#include "Utils.h"

int main()
{
    std::string workPath = utils::FileSystem::currentWorkPath();
    if (!workPath.empty())
    {
        std::cout << "current work path: " << workPath << std::endl;
    }
    else
    {
        std::cout << "work path is invaild" << std::endl;
    }

    std::string path = "..";
    bool ok = utils::FileSystem::setCurrentWorkPath(path);
    if (ok)
    {
        std::cout << "set current work path success, work path: " << utils::FileSystem::currentWorkPath() << std::endl;
    }
    else
    {
        std::cout << "set current work path failed" << std::endl;
    }

    std::string exePath = utils::FileSystem::currentExePath();
    if (!exePath.empty())
    {
        std::cout << "exe path: " << exePath << std::endl;
    }
    else
    {
        std::cout << "exe path is invaild" << std::endl;
    }

    utils::FileSystem::setCurrentWorkPath(utils::FileSystem::currentExePath());
    std::cout << "work path: " << utils::FileSystem::currentWorkPath() << std::endl;

    std::string exeName = utils::FileSystem::currentExeName();
    if (!exeName.empty())
    {
        std::cout << "exe name: " << exeName << std::endl;
    }
    else
    {
        std::cout << "exe name is invaild" << std::endl;
    }

    std::cout << "hello.txt is exists? : " << utils::FileSystem::isExists("hello.txt") << std::endl;
    std::cout << "Makefile is exists? : " << utils::FileSystem::isExists("Makefile") << std::endl;
    std::cout << "test dir is exists? : " << utils::FileSystem::isExists("test") << std::endl;
    std::cout << "test/hello.txt is exists? : " << utils::FileSystem::isExists("test/hello.txt") << std::endl;

    std::string dirPath = "hello/test/aaa";
    ok = utils::FileSystem::mkdir(dirPath);
    if (ok)
    {
        std::cout << "create " << dirPath << " success" << std::endl;
    }
    else
    {
        std::cout << "create " << dirPath << " failed" << std::endl;
    }
    
    dirPath = "aaa";
    ok = utils::FileSystem::mkdir(dirPath);
    if (ok)
    {
        std::cout << "create " << dirPath << " success" << std::endl;
    }
    else
    {
        std::cout << "create " << dirPath << " failed" << std::endl;
    }

    dirPath = "hello.txt";
    ok = utils::FileSystem::remove(dirPath);
    if (ok)
    {
        std::cout << "remove " << dirPath << " success" << std::endl;
    }
    else
    {
        std::cout << "remove " << dirPath << " failed" << std::endl;
    }

    return 0;
}
