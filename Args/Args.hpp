#ifndef _ARGS_H
#define _ARGS_H

#include <iostream>

/**********模板递归和特化方式展开参数包******************/

// 前向申明
template<typename... Args>
struct Sum;

// 基本定义
#if 0
// 枚举编译器常量
template<typename First, typename... Rest>
struct Sum<First, Rest...>
{
    enum
    {
        value = Sum<First>::value + Sum<Rest...>::value
    };
};
#else
// 继承了编译器常量std::integral_constant
template<typename First, typename... Rest>
struct Sum<First, Rest...> : std::integral_constant<int, Sum<First>::value + Sum<Rest...>::value> {};
#endif

// 终止递归
#if 0
template<typename Last>
struct Sum<Last>
{
    enum
    {
        value = sizeof(Last)
    };
};
#else
template<typename Last>
struct Sum<Last> : std::integral_constant<int, sizeof(Last)> {};
#endif

/**********继承和特化方式展开参数包******************/

// 整型序列的定义
template<int...>
struct IndexSeq {};

#if 0
// 继承方式，开始展开参数包
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};
#else
// using实现来展开参数包
template<int N, int... Indexes>
struct MakeIndexes
{
    using type = typename MakeIndexes<N - 1, N - 1, Indexes...>::type;
};
#endif

// 模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    using type = IndexSeq<Indexes...>;
};

#endif
