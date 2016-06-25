#ifndef _ANY_H
#define _ANY_H

#include <iostream>
#include <memory>
#include <typeindex>

class Any
{
public:
    Any() : m_typeIndex(std::type_index(typeid(void))) {}
    Any(Any& other) : m_basePtr(other.clone()), m_typeIndex(other.m_typeIndex) {}
    Any(Any&& other) : m_basePtr(std::move(other.m_basePtr)), m_typeIndex(other.m_typeIndex) {}

    template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
    Any(U&& value)
        : m_basePtr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
        m_typeIndex(std::type_index(typeid(typename std::decay<U>::type))) {}

    bool isNull() const
    {
        return !bool(m_basePtr);
    }

    template<typename U>
    bool is() const
    {
        return m_typeIndex == std::type_index(typeid(U));
    }

    template<typename U>
    U& anyCast()
    {
        if (!is<U>())
        {
            std::cout << "Can not cast " << typeid(U).name() << " to " << m_typeIndex.name() << std::endl;
            throw std::bad_cast();
        }

        auto dervied = dynamic_cast<Derived<U>*>(m_basePtr.get());
        return dervied->m_value;
    }

    Any& operator=(const Any& other)
    {
        if (m_basePtr == other.m_basePtr)
        {
            return *this;
        }

        m_basePtr = other.clone();
        m_typeIndex = other.m_typeIndex;
        return *this;
    }

private:
    class Base;
    using BasePtr = std::unique_ptr<Base>;

    class Base
    {
    public:
        virtual ~Base() {}
        virtual BasePtr clone() const = 0;
    };

    template<typename T>
    class Derived : public Base
    {
    public:
        template<typename U>
        Derived(U&& value) : m_value(std::forward<U>(value)) {}

        virtual BasePtr clone() const override
        {
            return BasePtr(new Derived<T>(m_value));
        }

        T m_value;
    };

    BasePtr clone() const
    {
        if (m_basePtr != nullptr)
        {
            return m_basePtr->clone();
        }
        return nullptr;
    }

    BasePtr m_basePtr;
    std::type_index m_typeIndex;    
};

#endif
