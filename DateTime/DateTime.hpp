#ifndef _DATETIME_H
#define _DATETIME_H

#include <ctime>
#include <string>
#include <type_traits>

class DateTime
{
public:
    template<typename T>
    static typename std::enable_if<std::is_same<std::string, T>::value, std::string>::type convert(time_t t)
    {
        return time2string(t);
    }

    template<typename T>
    static typename std::enable_if<std::is_same<time_t, T>::value, time_t>::type convert(const std::string& timeStr)
    {
        return string2time(timeStr);
    }

    static std::string currentTime()
    {
        return time2string(time(nullptr));
    }

private:
    static std::string time2string(time_t t)
    {
        struct tm* tmNow = localtime(&t);
        char timeStr[sizeof("yyyy-mm-dd hh:mm:ss")] = {'\0'};
        std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tmNow);
        return timeStr;
    }
    
    static time_t string2time(const std::string& timeStr)
    {
        struct tm stTm;
        sscanf(timeStr.c_str(), "%d-%d-%d %d:%d:%d",
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
};

#endif
