#ifndef _VARIANT_H
#define _VARIANT_H

#include <iostream>
#include <typeindex>

template<std::size_t arg, std::size_t... rest>
struct IntergerMax;

template<std::size_t arg>
struct IntergerMax<arg> : std::integral_constant<std::size_t, arg> {};

template<std::size_t arg1, std::size_t arg2, std::size_t... rest>
struct IntergerMax<arg1, arg2, rest...> : std::integral_constant<std::size_t, arg1 >= arg2 ? IntergerMax<arg1, rest...>::value : IntergerMax<arg2, rest...>::value> {};

#endif
