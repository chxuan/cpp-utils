#ifndef _TUPLE_HELPER_H
#define _TUPLE_HELPER_H

#include <iostream>
#include <tuple>
#include <array>
#include <utility>

/***********递归+特化方式遍历打印tuple***************/
template<typename Tuple, std::size_t N>
struct tuple_printer
{
    static void print(const Tuple& t)
    {
        tuple_printer<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct tuple_printer<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<typename... Args>
void print_tuple(const std::tuple<Args...>& t)
{
    tuple_printer<decltype(t), sizeof...(Args)>::print(t);
    std::cout << std::endl;
}

/***********使用流的方式，这里用到了C++14的index_sequence****************/
template<typename Char, typename Traits, typename Tuple, std::size_t... Index>
void print_tuple_impl(std::basic_ostream<Char, Traits>& os, const Tuple& t, std::index_sequence<Index...>)
{
    using swallow = int[]; // guaranties left to right order
    (void)swallow { 0, (void(os << (Index == 0 ? "" : ", ") << std::get<Index>(t)), 0)... };
}

template<typename Char, typename Traits, typename... Args>
decltype(auto) operator<<(std::basic_ostream<Char, Traits>& os, const std::tuple<Args...>& t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}

/***********将std::array转换成std::tuple，这里用到了C++14的index_sequence****************/
template<typename Array, std::size_t... Index>
decltype(auto) array2tuple_impl(const Array& a, std::index_sequence<Index...>)
{
    return std::make_tuple(a[Index]...);
}

template<typename T, std::size_t N>
decltype(auto) array2tuple(const std::array<T, N>& a)
{
    return array2tuple_impl(a, std::make_index_sequence<N>{});
}

/***********通过元素类型获取元素的值****************/
template<typename T, std::size_t N, typename... Args>
struct index_of;

template<typename T, std::size_t N, typename... Args>
struct index_of<T, N, T, Args...> : std::integral_constant<int, N> {};

template<typename T, std::size_t N, typename U, typename... Args>
struct index_of<T, N, U, Args...> : std::integral_constant<int, index_of<T, N + 1, Args...>::value> {};

template<typename T, std::size_t N>
struct index_of<T, N> : std::integral_constant<int, -1> {};

template<typename T, typename... Args>
T get_element_by_type(const std::tuple<Args...>& t)
{
    return std::get<index_of<T, 0, Args...>::value>(t);
}

/***********通过std::tuple作为参数调用函数****************/
template<typename Function, typename Tuple, std::size_t... Index>
decltype(auto) invoke_impl(Function&& func, Tuple&& t, std::index_sequence<Index...>)
{
    return func(std::get<Index>(std::forward<Tuple>(t))...);
}

template<typename Function, typename Tuple>
decltype(auto) invoke(Function&& func, Tuple&& t)
{
    constexpr auto size = std::tuple_size<typename std::decay<Tuple>::type>::value;
    return invoke_impl(std::forward<Function>(func), std::forward<Tuple>(t), std::make_index_sequence<size>{});
}

/***********make_from_tuple****************/
template<typename T, typename Tuple, std::size_t... Index>
decltype(auto) make_from_tuple_impl(Tuple&& t, std::index_sequence<Index...>)
{
    return T{std::get<Index>(std::forward<Tuple>(t))...};
}

template<typename T, typename Tuple>
decltype(auto) make_from_tuple(Tuple&& t)
{
    constexpr auto size = std::tuple_size<typename std::decay<Tuple>::type>::value;
    return make_from_tuple_impl<T>(std::forward<Tuple>(t), std::make_index_sequence<size>{});
}

#endif
