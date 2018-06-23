#pragma once
/*
功能:格式化字符串
日期:2018-06-22
作者:chxuan <787280310@qq.com>
*/
#include <string.h>
#include <string>
#include <tuple>
#include <type_traits>
#include "lexical_cast.h"

template<std::size_t i, typename Tuple>
inline typename std::enable_if<(i == std::tuple_size<Tuple>::value), std::string>::type 
get_arg_by_index(Tuple&, std::size_t)
{
    throw std::invalid_argument("Arg index out of range");
}

template<std::size_t i, typename Tuple>
inline typename std::enable_if<(i < std::tuple_size<Tuple>::value), std::string>::type 
get_arg_by_index(Tuple& tp, std::size_t index)
{
    if (i == index)
    {
        return lexical_cast<std::string>(std::get<i>(tp));
    }
    else
    {
        return get_arg_by_index<i + 1>(tp, index);
    }
}

template<typename... Args>
inline std::string format(const char* str, Args&&... args)
{
    std::string buf;
    auto tp = std::tuple<Args...>(args...);
    char* curr = const_cast<char*>(str);
    char* last = curr;
    int pos = -1;

    while (true)
    {
        if (*curr == '{' && *(curr + 1) == '}') 
        {
            int len = curr - last;
            if (len != 0)
            {
                buf.append(last, len);
            }

            buf.append(get_arg_by_index<0>(tp, ++pos));

            last = curr + 2;
            ++curr;
        }
        else if (*curr == '\0')
        {
            int len = curr - last;
            if (len != 0)
            {
                buf.append(last, len);
            }
            break;
        }

        ++curr;
    }

    return buf;
}

template<typename... Args>
inline std::string format(const std::string& str, Args&&... args)
{
    return format(str.c_str(), std::forward<Args>(args)...);
}
