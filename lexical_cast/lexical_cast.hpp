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

const char* strue = "true";
const char* sfalse = "false";

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

template<typename From>
struct Converter<long, From>
{
    static long convert(const std::string& from)
    {
        return std::atol(from.c_str());
    }

    static long convert(const char* from)
    {
        return std::atol(from);
    }
};

template<typename From>
struct Converter<long long, From>
{
    static long long convert(const std::string& from)
    {
        return std::atoll(from.c_str());
    }

    static long long convert(const char* from)
    {
        return std::atoll(from);
    }
};

template<typename From>
struct Converter<double, From>
{
    static double convert(const std::string& from)
    {
        return std::atof(from.c_str());
    }

    static double convert(const char* from)
    {
        return std::atof(from);
    }
};

template<typename From>
struct Converter<float, From>
{
    static float convert(const std::string& from)
    {
        return static_cast<float>(std::atof(from.c_str()));
    }

    static float convert(const char* from)
    {
        return static_cast<float>(std::atof(from));
    }
};

// to bool
template<typename From>
struct Converter<bool, From>
{
    static typename std::enable_if<std::is_integral<From>::value, bool>::type convert(From from)
    {
        return from > 0 ? true : false;
    }
};

// to string
template<typename From>
struct Converter<std::string, From>
{
    static std::string convert(const From& from)
    {
        return std::to_string(from);
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
