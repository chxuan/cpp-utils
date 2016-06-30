#ifndef _VARIANT_H
#define _VARIANT_H

#include <iostream>
#include <typeindex>

/*获取最大的整数*/
template<std::size_t arg, std::size_t... rest>
struct IntergerMax;

template<std::size_t arg>
struct IntergerMax<arg> : std::integral_constant<std::size_t, arg> {};

template<std::size_t arg1, std::size_t arg2, std::size_t... rest>
struct IntergerMax<arg1, arg2, rest...> : std::integral_constant<std::size_t, arg1 >= arg2 ? IntergerMax<arg1, rest...>::value : IntergerMax<arg2, rest...>::value> {};

/*获取最大的align*/
template<typename... Args>
struct MaxAlign : std::integral_constant<int, IntergerMax<std::alignment_of<Args>::value...>::value> {};

/*是否包含某个类型*/
template<typename T, typename... List>
struct Contains;

template<typename T, typename Head, typename... Rest>
struct Contains<T, Head, Rest...> : std::conditional<std::is_same<T, Head>::value, std::true_type, Contains<T, Rest...>>::type {};

template<typename T>
struct Contains<T> : std::false_type {};


#endif
