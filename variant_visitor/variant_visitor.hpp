#ifndef _VARIANT_VISITOR_H
#define _VARIANT_VISITOR_H

#include <utility>
#include <type_traits>

template<typename Function, typename... Args>
struct make_overload_impl : make_overload_impl<Function>::type, 
                            make_overload_impl<Args...>::type
{
    using type = make_overload_impl;
    using make_overload_impl<Function>::type::operator();
    using make_overload_impl<Args...>::type::operator();
    constexpr explicit make_overload_impl(Function&& func, Args&&... args)
        : make_overload_impl<Function>::type(std::forward<Function>(func)),
        make_overload_impl<Args...>::type(std::forward<Args>(args)...)
    {}
};

template<typename Function>
struct make_overload_impl<Function>
{
    using type = Function;
};

template<typename Return, typename... Args>
struct make_overload_impl<Return(*)(Args...)>
{
    using type = make_overload_impl;
    using Function = Return(*)(Args...);
    constexpr explicit make_overload_impl(const Function&& func) : _func(func) {}
    constexpr Return operator()(Args&&... args) const
    {
        return _func(std::forward<Args>(args)...);
    }

private:
    Function _func;
};

struct make_overload
{
    template<typename... Function, typename Overload = 
        typename make_overload_impl<typename std::decay<Function>::type...>::type>
    constexpr Overload operator()(Function&&... func) const
    {
        return Overload(std::forward<Function>(func)...);
    }
};

template<typename... Args>
auto make_visitor(Args&&... args)
{
    return make_overload()(std::forward<Args>(args)...);
}

#endif
