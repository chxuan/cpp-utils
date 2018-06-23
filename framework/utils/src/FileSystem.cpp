/* Copyright(C)
 * For free
 * All right reserved
 * 
 */
/**
 * @file FileSystem.cpp
 * @brief 文件系统工具实现
 * @author highway-9, 787280310@qq.com
 * @version 1.1.0
 * @date 2015-11-28
 */

#include "FileSystem.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>

#ifndef PATH_MAX
#define PATH_MAX        1024        // 默认最大路径长度
#endif

namespace utils
{
std::string FileSystem::currentWorkPath()
{
    char buf[PATH_MAX] = {'\0'};
    if (getcwd(buf, sizeof (buf) - 1) != NULL)
    {
        return buf;
    }

    return "";
}

bool FileSystem::setCurrentWorkPath(const std::string& path)
{
    int ret = chdir(path.c_str());
    return ret == -1 ? false : true;
}

std::string FileSystem::currentExePath()
{
    char buf[PATH_MAX] = {'\0'};

    int ret = readlink("/proc/self/exe", buf, PATH_MAX);
    if (ret < 0 || ret >= PATH_MAX)
    {
        return "";
    }

    std::string path(buf);
    int pos = path.find_last_of("/");
    if (pos == -1)
    {
        return "";
    }

    path = path.substr(0, pos);

    return path;
}

std::string FileSystem::currentExeName()
{
    char buf[PATH_MAX] = {'\0'};

    int ret = readlink("/proc/self/exe", buf, PATH_MAX);
    if (ret < 0 || ret >= PATH_MAX)
    {
        return "";
    }

    std::string path(buf);
    int pos = path.find_last_of("/");
    if (pos == -1)
    {
        return "";
    }

    path = path.substr(pos + 1, path.size() - 1);

    return path;
}

bool FileSystem::isExists(const std::string& path)
{
    // F_OK 用于判断文件是否存在
    int ret = access(path.c_str(), F_OK);
    return ret == -1 ? false : true;
}

bool FileSystem::mkdir(const std::string& path)
{
    if (path.empty())
    {
        return false;
    }

    if (FileSystem::isExists(path))
    {
        return true;
    }

    std::string dirPath = path;
    if (dirPath[dirPath.size() - 1] != '/')
    {
        dirPath += '/';
    }

    for (unsigned int i = 0; i < dirPath.size(); ++i)
    {
        if (dirPath[i] == '/') 
        {
            if (i == 0)
            {
                continue;
            }

            std::string tempPath = dirPath.substr(0, i);
            if (!FileSystem::isExists(tempPath))
            {
                if (::mkdir(tempPath.c_str(), 0755) == -1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool FileSystem::remove(const std::string& path)
{
    if (path.empty())
    {
        return false;
    }

    if (!FileSystem::isExists(path))
    {
        return false;
    }

    int ret = ::remove(path.c_str());
    return ret == -1 ? false : true;
}
}
