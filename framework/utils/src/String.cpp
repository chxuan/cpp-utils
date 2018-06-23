/* Copyright(C)
 * For free
 * All right reserved
 * 
 */
/**
 * @file String.cpp
 * @brief 字符串转换工具实现
 * @author highway-9, 787280310@qq.com
 * @version 1.1.0
 * @date 2015-11-28
 */

#include "String.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace utils
{
std::string String::int32ToString(int n)
{
    return tToString(n);
}

std::string String::uint32ToString(unsigned int n)
{
    return tToString(n);
}

std::string String::int64ToString(long long n)
{
    return tToString(n);
}

std::string String::uint64ToString(unsigned long long n)
{
    return tToString(n);
}

std::string String::floatToString(float n)
{
    return tToString(n);
}

std::string String::doubleToString(double n)
{
    return tToString(n);
}

std::string String::time_tToString(time_t n)
{
    struct tm* p;
    p = localtime(&n);

    p->tm_year += 1900;
    p->tm_mon++;

    char time[50] = {'\0'};
    sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d",
           p->tm_year,
           p->tm_mon,
           p->tm_mday,
           p->tm_hour,
           p->tm_min,
           p->tm_sec);

    return time;
}

bool String::stringToInt32(const std::string& str, int& n)
{
    return stringToT(str, n);
}

bool String::stringToUint32(const std::string& str, unsigned int& n)
{
    return stringToT(str, n);
}

bool String::stringToInt64(const std::string& str, long long& n)
{
    return stringToT(str, n);
}

bool String::stringToUint64(const std::string& str, unsigned long long& n)
{
    return stringToT(str, n);
}

bool String::stringToFloat(const std::string& str, float& n)
{
    return stringToT(str, n);
}

bool String::stringToDouble(const std::string& str, double& n)
{
    return stringToT(str, n);
}

time_t String::stringToTime_t(const std::string& time)
{
    struct tm stTm;

    sscanf(time.c_str(), "%d-%d-%d %d:%d:%d",
            &(stTm.tm_year),
            &(stTm.tm_mon),
            &(stTm.tm_mday),
            &(stTm.tm_hour),
            &(stTm.tm_min),
            &(stTm.tm_sec));

    stTm.tm_year -= 1900;
    stTm.tm_mon--;
    stTm.tm_isdst = -1;

    return mktime(&stTm);
}
}
