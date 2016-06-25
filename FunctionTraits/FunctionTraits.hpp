#ifndef _FUNCTIONTRAITS_H
#define _FUNCTIONTRAITS_H

#include <functional>
#include <tuple>

// 转换为std::function和函数指针 
template<typename T>
class FunctionTraits;

// 普通函数
template<typename Ret, typename... Args>
class FunctionTraits<Ret(Args...)>
{
public:
	enum 
    {
        Arity = sizeof...(Args) 
    };
	typedef Ret FunctionType(Args...);
	typedef Ret ReturnType;
	using StlFunctionType = std::function<FunctionType>;
    using Pointer = Ret(*)(Args...);

	template<size_t I>
	class args
	{
		static_assert(I < Arity, "Index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
	};
};

// 函数指针
template<typename Ret, typename... Args>
class FunctionTraits<Ret(*)(Args...)> : public FunctionTraits<Ret(Args...)>{};

// std::function
template <typename Ret, typename... Args>
class FunctionTraits<std::function<Ret(Args...)>> : public FunctionTraits<Ret(Args...)>{};

// 成员函数
#define MEMBER_FUNTION_TRAITS(...) \
template <typename ReturnType, typename ClassType, typename... Args> \
class FunctionTraits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : public FunctionTraits<ReturnType(Args...)>{}; \

MEMBER_FUNTION_TRAITS()
MEMBER_FUNTION_TRAITS(const)
MEMBER_FUNTION_TRAITS(volatile)
MEMBER_FUNTION_TRAITS(const volatile)

// 函数对象
template<typename Callable>
class FunctionTraits : public FunctionTraits<decltype(&Callable::operator())>{};

template <typename Function>
typename FunctionTraits<Function>::StlFunctionType toFunction(const Function& lambda)
{
	return static_cast<typename FunctionTraits<Function>::StlFunctionType>(lambda);
}

template <typename Function>
typename FunctionTraits<Function>::StlFunctionType toFunction(Function&& lambda)
{
	return static_cast<typename FunctionTraits<Function>::StlFunctionType>(std::forward<Function>(lambda));
}

template <typename Function>
typename FunctionTraits<Function>::Pointer toFunctionPointer(const Function& lambda)
{
	return static_cast<typename FunctionTraits<Function>::Pointer>(lambda);
}

#endif
