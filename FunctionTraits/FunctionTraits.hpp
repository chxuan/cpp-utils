#ifndef _FUNCTIONTRAITS_H
#define _FUNCTIONTRAITS_H

#include <functional>
#include <tuple>

// 转换为std::function和函数指针 
template<typename T>
struct FunctionTraits;

// 普通函数
template<typename Ret, typename... Args>
struct FunctionTraits<Ret(Args...)>
{
	enum 
    {
        arity = sizeof...(Args) 
    };
	typedef Ret functionType(Args...);
    using returnType = Ret;
	using stlFunctionType = std::function<functionType>;
    using pointer = Ret(*)(Args...);

#if 0
    template<std::size_t N>
    using argType = typename std::tuple_element<N, std::tuple<Args...>>::type;
#else
	template<std::size_t N>
	struct args
	{
		static_assert(N < arity, "Index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	};
#endif
};

// 函数指针
template<typename Ret, typename... Args>
struct FunctionTraits<Ret(*)(Args...)> : public FunctionTraits<Ret(Args...)>{};

// std::function
template <typename Ret, typename... Args>
struct FunctionTraits<std::function<Ret(Args...)>> : public FunctionTraits<Ret(Args...)>{};

// 成员函数
#define MEMBER_FUNTION_TRAITS(...) \
template <typename ReturnType, typename ClassType, typename... Args> \
struct FunctionTraits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : public FunctionTraits<ReturnType(Args...)>{}; \

MEMBER_FUNTION_TRAITS()
MEMBER_FUNTION_TRAITS(const)
MEMBER_FUNTION_TRAITS(volatile)
MEMBER_FUNTION_TRAITS(const volatile)

// 函数对象
template<typename Callable>
struct FunctionTraits : public FunctionTraits<decltype(&Callable::operator())>{};

template <typename Function>
typename FunctionTraits<Function>::stlFunctionType toFunction(const Function& lambda)
{
	return static_cast<typename FunctionTraits<Function>::stlFunctionType>(lambda);
}

template <typename Function>
typename FunctionTraits<Function>::stlFunctionType toFunction(Function&& lambda)
{
	return static_cast<typename FunctionTraits<Function>::stlFunctionType>(std::forward<Function>(lambda));
}

template <typename Function>
typename FunctionTraits<Function>::pointer toFunctionPointer(const Function& lambda)
{
	return static_cast<typename FunctionTraits<Function>::pointer>(lambda);
}

#endif
