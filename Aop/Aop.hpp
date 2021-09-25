#ifndef _AOP_H
#define _AOP_H

#include <iostream>
#include <typeinfo>
#include <type_traits>

#define HAS_MEMBER(member) \
template<typename T, typename... Args> \
class HasMember##member \
{ \
private: \
    template<typename U> \
    static auto check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
    template<typename U> \
    static std::false_type check(...); \
public: \
    enum \
    { \
        value = std::is_same<decltype(check<T>(0)), std::true_type>::value \
    }; \
}; \

HAS_MEMBER(foo)
HAS_MEMBER(before)
HAS_MEMBER(after)

template<typename Function, typename... Args>
class Aspect
{
public:
    Aspect() = delete;
    Aspect(const Aspect&) = delete;
    Aspect& operator=(const Aspect&) = delete;

    Aspect(Function&& func)
        : m_func(std::forward<Function>(func))
    {
        // Do nothing
    }

    template<typename T>
    typename std::enable_if<HasMemberbefore<T, Args...>::value && HasMemberafter<T, Args...>::value>::type invoke(Args&&... args, T&& asp)
    {
        asp.before(std::forward<Args>(args)...); // 核心逻辑之前的切面逻辑
        m_func(std::forward<Args>(args)...);     // 核心逻辑
        asp.after(std::forward<Args>(args)...);  // 核心逻辑之后的切面逻辑
    }

    template<typename T>
    typename std::enable_if<HasMemberbefore<T, Args...>::value && !HasMemberafter<T, Args...>::value>::type invoke(Args&&... args, T&& asp)
    {
        asp.before(std::forward<Args>(args)...); // 核心逻辑之前的切面逻辑
        m_func(std::forward<Args>(args)...);     // 核心逻辑
    }

    template<typename T>
    typename std::enable_if<!HasMemberbefore<T, Args...>::value && HasMemberafter<T, Args...>::value>::type invoke(Args&&... args, T&& asp)
    {
        m_func(std::forward<Args>(args)...);     // 核心逻辑
        asp.after(std::forward<Args>(args)...);  // 核心逻辑之后的切面逻辑
    }

    template<typename Head, typename... Tail>
    typename std::enable_if<HasMemberbefore<Head, Args...>::value && HasMemberafter<Head, Args...>::value>::type invoke(Args&&... args, Head&& headAsp, Tail&&... tailAsp)
    {
        headAsp.before(std::forward<Args>(args)...);
        invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAsp)...);
        headAsp.after(std::forward<Args>(args)...);
    }

    template<typename Head, typename... Tail>
    typename std::enable_if<!HasMemberbefore<Head, Args...>::value && HasMemberafter<Head, Args...>::value>::type invoke(Args&&... args, Head&& headAsp, Tail&&... tailAsp)
    {
        invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAsp)...);
        headAsp.after(std::forward<Args>(args)...);
    }

    template<typename Head, typename... Tail>
    typename std::enable_if<HasMemberbefore<Head, Args...>::value && !HasMemberafter<Head, Args...>::value>::type invoke(Args&&... args, Head&& headAsp, Tail&&... tailAsp)
    {
        headAsp.before(std::forward<Args>(args)...);
        invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAsp)...);
    }
private:
    Function m_func = nullptr; // 被织入的函数
};

template<typename T> 
using identity_t = T;

// AOP的辅助函数，简化调用
template<typename... AOP, typename Function, typename... Args>
void aopInvoke(Function&& func, Args&&... args)
{
    Aspect<Function, Args...> asp(std::forward<Function>(func));
    asp.invoke(std::forward<Args>(args)..., identity_t<AOP>()...);
}

#endif
