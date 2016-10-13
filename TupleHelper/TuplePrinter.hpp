#ifndef _TUPLEPRINTER_H
#define _TUPLEPRINTER_H

#include <iostream>
#include <tuple>
#include <array>
#include <utility>

/***********递归+偏特化方式遍历打印tuple***************/
template<typename Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<typename... Args>
void printTuple(const std::tuple<Args...>& t)
{
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
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

#endif
