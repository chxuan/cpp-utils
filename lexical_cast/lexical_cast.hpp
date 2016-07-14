#ifndef _LEXICAL_CAST_H
#define _LEXICAL_CAST_H

#include <cctype>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

namespace detail
{

template<typename To, typename From>
struct Converter {};

// to numeric
template<typename From>
struct Converter<int, From>
{
    static int convert(const std::string& from)
    {
        return std::atoi(from.c_str());
    }

    static int convert(const char* from)
    {
        return std::atoi(from);
    }
};

};

template<typename To, typename From>
typename std::enable_if<!std::is_same<To, From>::value, To>::type lexical_cast(const From& from)
{
    return detail::Converter<To, From>::convert(from);
}

template<typename To, typename From>
typename std::enable_if<std::is_same<To, From>::value, To>::type lexical_cast(const From& from)
{
    return from;
}

#endif
