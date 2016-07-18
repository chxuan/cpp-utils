#ifndef _LINQCPP_H
#define _LINQCPP_H

#include <type_traits>
#include <numeric>
#include <boost/algorithm/minmax_element.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/join.hpp>

namespace linqcpp
{

// 定义FunctionTraits用于将lambda表达式转换成function.
template<typename Function>
struct FunctionTraits : public FunctionTraits<decltype(&Function::operator())> {};

template<typename ClassType, typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType(ClassType::*)(Args...) const>
{
    using function = std::function<ReturnType(Args...)>;
};

template<typename Function>
typename FunctionTraits<Function>::function toFunction(const Function& lambda)
{
    return static_cast<typename FunctionTraits<Function>::function>(lambda);
}

template<typename R>
class LinqCpp
{
public:
    using valueType = typename R::value_type;
    LinqCpp(R range) : m_linqRange(range) {}

    // 过滤操作.
    template<typename F>
    auto where(const F& f)->LinqCpp<boost::filtered_range<typename FunctionTraits<F>::function, R>>
    {
        auto func = toFunction(f);
        return LinqCpp<boost::filtered_range<typename FunctionTraits<F>::function, R>>(boost::adaptors::filter(m_linqRange, func));
    }

    // 转换操作.
    template<typename F>
    auto select(const F& f)->LinqCpp<boost::transformed_range<typename FunctionTraits<F>::function, R>>
    {
        auto func = toFunction(f);
        return LinqCpp<boost::transformed_range<typename FunctionTraits<F>::function, R>>(boost::adaptors::transform(m_linqRange, func));
    }

    auto begin() const->decltype(std::begin(std::declval<const R>()))
    {
        return std::begin(m_linqRange);
    }

    auto end() const->decltype(std::end(std::declval<const R>()))
    {
        return std::end(m_linqRange);
    }

    // 翻转操作.
    auto reverse()->LinqCpp<boost::reversed_range<R>>
    {
        return LinqCpp<boost::reversed_range<R>>(boost::adaptors::reverse(m_linqRange));
    }

    template<typename F>
    auto first(const F& f)->valueType
    {
        return *std::find_if(begin(), end(), f);
    }

    template<typename F>
    auto last(const F& f)->valueType
    {
        return reverse().first(f); 
    }

    bool empty() const
    {
        return begin() == end();
    }

    auto max() const->valueType
    {
        return *std::max_element(begin(), end());
    }

    template<typename F>
    auto max(const F& f) const->valueType
    {
        return *std::max_element(begin(), end(), f);
    }

    auto min() const->valueType
    {
        return *std::min_element(begin(), end());
    }

    template<typename F>
    auto min(const F& f) const->valueType
    {
        return *min_element(begin(), end(), f);
    }

    auto minmax() const->decltype(std::minmax_element(begin(), end()))
    {
        return std::minmax_element(begin(), end());
    }

    template<typename F>
    auto minmax(const F& f) const->decltype(std::minmax_element(begin(), end(), f))
    {
        return std::minmax_element(begin(), end(), f);
    }

    // 累加器，对每一个元素进行一个运算.
    template<typename F>
    auto aggregate(const F& f) const->valueType
    {
        auto iter = begin();
        auto value = *iter++;
        return std::accumulate(iter, end(), std::move(value), f);
    }

    auto sum() const->valueType
    {
        return aggregate(std::plus<valueType>());
    }

    auto count() const->decltype(std::distance(begin(), end()))
    {
        return std::distance(begin(), end());
    }

    // 根据function求count.
    template<typename F>
    auto count(const F& f) const->decltype(std::count_if(begin(), end(), f))
    {
        return std::count_if(begin(), end(), f);
    }

    auto average() const->valueType
    {
        return sum() / count();
    }

    // 简单去重.
    auto distinct()->LinqCpp<boost::range_detail::uniqued_range<R>>
    {
        return LinqCpp<boost::range_detail::uniqued_range<R>>(m_linqRange | boost::adaptors::uniqued);
    }

    // 根据判断式判断是否包含.
    template<typename F>
    auto contains(const F& f) const->bool
    {
        return std::find_if(begin(), end(), f) != end();
    }

    // 遍历操作.
    template<typename F>
    void foreach(const F& f) const
    {
        std::for_each(begin(), end(), f); 
    }

    // 存在满足条件的就返回true.
    template<typename F>
    auto any(const F& f) const->bool
    {
        return std::any_of(begin(), end(), f);
    }

    // 满足全部条件的就返回true.
    template<typename F>
    auto all(const F& f) const->bool
    {
        return std::all_of(begin(), end(), f);
    }

private:
    R m_linqRange;
};

};

// 简化Range的声明
template<template<typename T> class IteratorRange, typename R>
using Range = IteratorRange<decltype(std::begin(std::declval<R>()))>;

template<typename R>
using iteratorRange = Range<boost::iterator_range, R>;

// 简化定义LinqCpp的辅助函数
template<typename R>
linqcpp::LinqCpp<iteratorRange<R>> from(const R& range)
{
    return linqcpp::LinqCpp<iteratorRange<R>>(iteratorRange<R>(range));
}

#endif
