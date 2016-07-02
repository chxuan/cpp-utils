#ifndef _VARIANT_H
#define _VARIANT_H

#include <iostream>
#include <typeindex>

/*获取最大的整数*/
template<std::size_t arg, std::size_t... rest>
struct IntergerMax;

template<std::size_t arg>
struct IntergerMax<arg> : std::integral_constant<std::size_t, arg> {};

template<std::size_t arg1, std::size_t arg2, std::size_t... rest>
struct IntergerMax<arg1, arg2, rest...> : std::integral_constant<std::size_t, arg1 >= arg2 ? IntergerMax<arg1, rest...>::value : IntergerMax<arg2, rest...>::value> {};

/*获取最大的align*/
template<typename... Args>
struct MaxAlign : std::integral_constant<int, IntergerMax<std::alignment_of<Args>::value...>::value> {};

/*是否包含某个类型*/
template<typename T, typename... List>
struct Contains;

template<typename T, typename Head, typename... Rest>
struct Contains<T, Head, Rest...> : std::conditional<std::is_same<T, Head>::value, std::true_type, Contains<T, Rest...>>::type {};

template<typename T>
struct Contains<T> : std::false_type {};

template<typename T, typename... List>
struct IndexOf;

template<typename T, typename Head, typename... Rest>
struct IndexOf<T, Head, Rest...>
{
    enum
    {
        value = IndexOf<T, Rest...>::value + 1
    };
};

template<typename T>
struct IndexOf<T>
{
    enum
    {
        value = 0
    };
};

template<int index, typename... Types>
struct At;

template<int index, typename First, typename... Types>
struct At<index, First, Types...>
{
    using type = typename At<index - 1, Types...>::type;
};

template<typename T, typename... Types>
struct At<0, T, Types...>
{
    using type = T;
};

template<typename... Types>
class Variant
{
public:

private:
    void destory(const std::type_index& index, void* buf)
    {
        [](Types&&...){}((destory0<Types>(index, buf), 0)...);
    }

    template<typename T>
    void destory0(const std::type_index& index, void* buf)
    {
        if (index == std::type_index(typeid(T)))
        {
            reinterpret_cast<T*>(buf)->~T();
        }
    }

    void move(const std::type_index& oldIndex, void* oldValue, void* newValue)
    {
        [](Types&&...){}((move0<Types>(oldIndex, oldValue, newValue), 0)...);
    }

    template<typename T>
    void move0(const std::type_index& oldIndex, void* oldValue, void* newValue)
    {
        if (oldIndex == std::type_index(typeid(T)))
        {
            new (newValue)T(std::move(*reinterpret_cast<T*>(oldValue)));
        }
    }

private:
    enum
    {
        dataSize = IntergerMax<sizeof(Types)...>::value,
        alignSize = MaxAlign<Types...>::value
    };
    using data_t = typename std::aligned_storage<dataSize, alignSize>::type;
    data_t m_data;
    std::type_index m_typeIndex;
};


#endif
