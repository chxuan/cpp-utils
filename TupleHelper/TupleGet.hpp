#ifndef _TUPLEGET_H
#define _TUPLEGET_H

#include <tuple>

template<typename T, std::size_t N, typename... Args>
struct IndexOf;

template<typename T, std::size_t N, typename... Args>
struct IndexOf<T, N, T, Args...> : std::integral_constant<int, N> {};

template<typename T, std::size_t N, typename U, typename... Args>
struct IndexOf<T, N, U, Args...> : std::integral_constant<int, IndexOf<T, N + 1, Args...>::value> {};

template<typename T, std::size_t N>
struct IndexOf<T, N> : std::integral_constant<int, -1> {};

template<typename T, typename... Args>
T getElementByType(const std::tuple<Args...>& t)
{
    return std::get<IndexOf<T, 0, Args...>::value>(t);
}

#endif
