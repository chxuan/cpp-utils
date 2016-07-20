#ifndef _LINQCPP_H
#define _LINQCPP_H

#include <type_traits>
#include <numeric>
#include <vector>
#include <map>
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
    R m_linqRange;
public:
    using ValueType = typename R::value_type;
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
    auto first(const F& f)->ValueType
    {
        return *std::find_if(begin(), end(), f);
    }

    template<typename F>
    auto last(const F& f)->ValueType
    {
        return reverse().first(f); 
    }

    bool empty() const
    {
        return begin() == end();
    }

    auto max() const->ValueType
    {
        return *std::max_element(begin(), end());
    }

    template<typename F>
    auto max(const F& f) const->ValueType
    {
        return *std::max_element(begin(), end(), f);
    }

    auto min() const->ValueType
    {
        return *std::min_element(begin(), end());
    }

    template<typename F>
    auto min(const F& f) const->ValueType
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
    auto aggregate(const F& f) const->ValueType
    {
        auto iter = begin();
        auto value = *iter++;
        return std::accumulate(iter, end(), std::move(value), f);
    }

    auto sum() const->ValueType
    {
        return aggregate(std::plus<ValueType>());
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

    auto average() const->ValueType
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

    // 将map中的键放到一个range中.
    auto keys() const->LinqCpp<boost::select_first_range<R>>
    {
        return LinqCpp<boost::select_first_range<R>>(boost::adaptors::keys(m_linqRange));
    }

    // 将map中的值放到一个range中.
    auto values() const->LinqCpp<boost::select_second_const_range<R>>
    {
        return LinqCpp<boost::select_second_const_range<R>>(boost::adaptors::values(m_linqRange));
    }

    // 获取指定索引位置的元素.
    template<typename T>
    auto elementAt(T index) const->ValueType
    {
        return *std::next(begin(), index);
    }

    // 获取前面的n个元素
    template<typename T>
    auto take(T n) const->LinqCpp<decltype(boost::adaptors::slice(m_linqRange, 0, n))>
    {
        return LinqCpp(boost::adaptors::slice(m_linqRange, 0, n));
    }

    // 获取指定范围内的元素.
    template<typename T>
    auto take(T start, T end) const->LinqCpp<decltype(boost::adaptors::slice(m_linqRange, start, end))>
    {
        return LinqCpp(boost::adaptors::slice(m_linqRange, start, end));
    }

    // 当条件不满足时返回前面所有的元素.
    template<typename F>
    auto takewhile(const F& f) const->LinqCpp<decltype(boost::make_iterator_range(begin(), std::find_if(begin(), end(), f)))>
    {
        return LinqCpp(boost::make_iterator_range(begin(), std::find_if(begin(), end(), f)));
    }
    
    // 获取第n个元素之后的所有元素.
    template<typename T>
    auto skip(T n) const->LinqCpp<decltype(boost::make_iterator_range(begin() + n, end()))>
    {
        return LinqCpp(boost::make_iterator_range(begin() + n, end()));
    }

    // 当条件不满足时，获取后面所有的元素.
    template<typename F>
    auto skipwhile(const F& f) const->LinqCpp<decltype(boost::make_iterator_range(std::find_if_not(begin(), end(), f), end()))>
    {
        return LinqCpp(boost::make_iterator_range(std::find_if_not(begin(), end(), f), end()));
    }

    // 将range转换为vector.
    std::vector<ValueType> toVector()
    {
        return std::vector<ValueType>(begin(), end());
    }

    // 按步长挑选元素组成新集合.
    template<typename T>
    auto step(T n)->decltype(boost::adaptors::stride(m_linqRange, n))
    {
        return boost::adaptors::stride(m_linqRange, n);
    }

    // 直接将指针或者智能指针指向的内容组成新集合.
    auto indirect()->LinqCpp<boost::indirected_range<R>>
    {
        return LinqCpp<boost::indirected_range<R>>(boost::adaptors::indirect(m_linqRange));
    }

    // 连接操作.
    template<typename R2>
    auto concat(const R2& other)->LinqCpp<boost::joined_range<R, const R2>>
    {
        return LinqCpp<boost::joined_range<R, const R2>>(boost::join(m_linqRange, other));
    }

    // 排除操作.
    template<typename R2>
    void except(const R2& other, std::vector<ValueType>& out)
    {
        std::set_difference(begin(), end(), std::begin(other), std::end(other), std::back_inserter(out));
    }

    // 包含操作.
    template<typename R2>
    bool includes(const R2& other) const
    {
        return std::includes(begin(), end(), std::begin(other), std::end(other));
    }

    // 带函数判断的包含操作.
    template<typename R2, typename F>
    bool includes(const R2& other, const F& f) const
    {
        return std::includes(begin(), end(), std::begin(other), std::end(other), f);
    }

    // 分组操作.
    template<typename Fn>
    std::multimap<typename std::result_of<Fn(ValueType)>::type, ValueType> groupby(const Fn& f)
    {
        using keyType = decltype(std::declval<Fn>()(std::declval<ValueType>()));
        std::multimap<keyType, ValueType> m;
        std::for_each(begin(), end(), [&m, &f](ValueType item)
        {
            m.insert(std::make_pair(f(item), item)); 
        });
        return m;
    }

    // 允许指定键和值函数的分组操作.
    template<typename KeyFn, typename ValueFn>
    std::multimap<typename std::result_of<KeyFn(ValueType)>::type, typename std::result_of<ValueFn(ValueType)>::type>
    groupby(const KeyFn& kfn, const ValueFn& vfn)
    {
        using keyType = decltype(std::declval<KeyFn>()(std::declval<ValueType>()));
        using valType = decltype(std::declval<ValueFn>()(std::declval<ValueType>()));
        std::multimap<keyType, valType> m;
        std::for_each(begin(), end(), [&m, &kfn, &vfn](ValueType item)
        { 
            m.insert(std::make_pair(kfn(item), vfn(item)));
        });
        return m;
    }

    // 转换操作.
    template<typename T>
    auto cast()->LinqCpp<boost::transformed_range<std::function<T(ValueType)>, R>>
    {
        std::function<T(ValueType)> f = [](ValueType item){ return static_cast<T>(item); };
        return LinqCpp<boost::transformed_range<std::function<T(ValueType)>, R>>(select(f));
    }
    
    // 判断操作.
    template<typename R2>
    bool equals(const LinqCpp<R2>& other) const
    {
        return count() == other.count() && std::equal(begin(), end(), other.begin());
    }

    template<typename R2>
    bool operator==(const LinqCpp<R2>& other) const
    {
        return equals(other);
    }

    template<typename R2>
    bool operator!=(const LinqCpp<R2>& other) const
    {
        return !equals(other);
    }
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

// 合并range.
template<typename... Args>
auto zip(const Args&... args)->boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(args)...))>>
{
    auto begin = boost::make_zip_iterator(boost::make_tuple(std::begin(args)...));
    auto end = boost::make_zip_iterator(boost::make_tuple(std::end(args)...));
    return boost::make_iterator_range(begin, end);
}

#endif
