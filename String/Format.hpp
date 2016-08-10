#ifndef _FORMAT_H
#define _FORMAT_H

#include <string.h>
#include <string>
#include <tuple>
#include <type_traits>
#include <iostream>

namespace detail
{

static void formatArg(char*& buf, int i)
{
    int size = sprintf(buf, "%d", i);
    buf += size;
}

static void formatArg(char*& buf, long i)
{
    int size = sprintf(buf, "%ld", i);
    buf += size;
}

static void formatArg(char*& buf, long long i)
{
    int size = sprintf(buf, "%lld", i);
    buf += size;
}

static void formatArg(char*& buf, double i)
{
    int size = sprintf(buf, "%.6f", i);
    buf += size;
}

static void formatArg(char*& buf, const char* p)
{
    int len = strlen(p);
    memcpy(buf, p, len);
    buf += len;
}

static void formatArg(char*& buf, const std::string& str)
{
    memcpy(buf, str.c_str(), str.size());
    buf += str.size();
}

template<std::size_t i, typename Tuple>
static typename std::enable_if<(i == std::tuple_size<Tuple>::value)>::type 
getArgByIndex(std::size_t, Tuple&, char*&)
{
    throw std::invalid_argument("Arg index out of range");
}

template<std::size_t i = 0, typename Tuple>
static typename std::enable_if<(i < std::tuple_size<Tuple>::value)>::type 
getArgByIndex(std::size_t index, Tuple& tp, char*& p)
{
    if (i == index)
    {
        formatArg(p, std::get<i>(tp));
    }
    else
    {
        getArgByIndex<i + 1>(index, tp, p);
    }
}

static int getIndex(char*& p)
{
    char temp[3] = {'\0'};
    int i = 0;
    while (*p != '}' && *p != '\0')
    {
        if (i >= 2)
        {
            throw std::invalid_argument("Index is out of range");
        }

        if (std::isdigit(*p))
        {
            // push digit
            temp[i++] = *p;
            char next = *(p + 1);
            if (std::isdigit(next))
            {
                temp[i++] = next;
                p += 2;
                continue;
            }

            // validate arg
            if (!std::isspace(next) && next != '}')
            {
                throw std::invalid_argument("Invaild argument");
            }
        }
        ++p;
    }
    return i == 0 ? -1 : std::atoi(temp);
}

}

template<typename... Args>
static std::string format(char* str, Args... args)
{
    char arr[4096] = {'\0'};
    char* buf = arr;
    auto tp = std::tuple<Args...>(args...);

    char* p = str;
    char* original = p;
    int last = 0;
    while (true)
    {
        if (*p == '{') 
        {
            // copy context before {
            last = p - original;
            memcpy(buf, original, last);
            buf += last;

            // format args
            int index = detail::getIndex(p);
            if (index >= 0)
            {
                detail::getArgByIndex<0>(index, tp, buf);
            }

            // skip }
            original = p + 1;
        }
        else if (*p == '\0')
        {
            last = p - original;
            memcpy(buf, original, last);
            break;
        }
        ++p;
    }

    return arr;
}

#endif
