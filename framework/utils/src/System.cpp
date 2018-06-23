/* Copyright(C)
 * For free
 * All right reserved
 * 
 */
/**
 * @file System.cpp
 * @brief 系统相关调用工具实现
 * @author highway-9, 787280310@qq.com
 * @version 1.1.0
 * @date 2015-11-28
 */

#include "System.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <uuid/uuid.h>
#include <openssl/crypto.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

namespace utils
{
std::string System::uuid()
{
    uuid_t uuid;
    uuid_generate(uuid);
    
    char buf[37] = {'\0'};
    uuid_unparse_upper(uuid, buf);

    return buf;
}

std::string System::md5(const std::string& str)
{
    MD5_CTX hashCtx;
    unsigned char hashRet[MD5_DIGEST_LENGTH];

    int ret = MD5_Init(&hashCtx);
    if (ret == 0)
    {
        return "";
    }

    ret = MD5_Update(&hashCtx, str.c_str(), str.size());
    if (ret == 0)
    {
        return "";
    }

    ret = MD5_Final(hashRet, &hashCtx);
    if (ret == 0)
    {
        return "";
    }

    OPENSSL_cleanse(&hashCtx, sizeof (hashCtx));

    std::string md5Text;
    char buf[2] = {'\0'};

    for (int i = 0; i < MD5_DIGEST_LENGTH * 2; ++i)
    {
        memset(buf, '\0', sizeof (buf));
        if (i & 0x1)
        {
            sprintf(buf, "%x", (hashRet[i / 2]) & 0xf);
        }
        else
        {
            sprintf(buf, "%x", (hashRet[i / 2] >> 4) & 0xf);
        }
        md5Text += buf;
    }
    
    return md5Text;
}

std::string System::sha1(const std::string& str)
{
    SHA_CTX hashCtx;
    unsigned char hashRet[SHA_DIGEST_LENGTH];

    int ret = SHA1_Init(&hashCtx);
    if (ret == 0)
    {
        return "";
    }

    ret = SHA1_Update(&hashCtx, str.c_str(), str.size());
    if (ret == 0)
    {
        return "";
    }

    ret = SHA1_Final(hashRet, &hashCtx);
    if (ret == 0)
    {
        return "";
    }

    OPENSSL_cleanse(&hashCtx, sizeof (hashCtx));

    std::string sha1Text;
    char buf[2] = {'\0'};

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
    {
        memset(buf, '\0', sizeof (buf));
        sprintf(buf, "%02x", hashRet[i]);
        sha1Text += buf;
    }

    return sha1Text;
}

unsigned long System::totalMemery()
{
    struct sysinfo info;
    int ret = sysinfo(&info);

    return ret == -1 ? 0 : info.totalram;
}

unsigned long System::freeMemery()
{
    struct sysinfo info;
    int ret = sysinfo(&info);

    return ret == -1 ? 0 : info.freeram;
}
}
