#ifndef _OPTIONAL_H
#define _OPTIONAL_H

#include <type_traits>
#include <utility>
#include <stdexcept>

template<typename T>
class Optional
{
public:
    using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

    Optional() = default;
    Optional(const T& t)
    {
        create(t);
    }

    Optional(T&& t)
    {
        create(std::move(t));
    }

    ~Optional()
    {
        destroy();
    }

    Optional(const Optional& other)
    {
        if (other.isInit())
        {
            assign(other);
        }
    }

    Optional(Optional&& other)
    {
        if (other.isInit())
        {
            assign(std::move(other));
            other.destroy();
        }
    }

    Optional& operator=(Optional&& other)
    {
        assign(std::move(other));
        return *this;
    }

    Optional& operator=(const Optional& other)
    {
        assign(other);
        return *this;
    }

    template<typename... Args>
    void emplace(Args&&... args)
    {
        destroy();
        create(std::forward<Args>(args)...);
    }

    bool isInit() const
    {
        return m_isInit;
    }

    explicit operator bool() const
    {
        return isInit();
    }

    T& operator*()
    {
        if (isInit())
        {
            return *((T*)(&m_data));
        }
        throw std::logic_error("Try to get data in o optional which is not initialized");
    }

    const T& operator*() const
    {
        if (isInit())
        {
            return *((T*)(&m_data));
        }
        throw std::logic_error("Try to get data in o optional which is not initialized");
    }

    T* operator->()
    {
        return &operator*();
    }

    const T* operator->() const
    {
        return &operator*();
    }

    bool operator==(const Optional<T>& rhs) const
    {
        return (!bool(*this)) != (!rhs) ? false : (!bool(*this) ? true : (*(*this)) == (*rhs));
    }

    bool operator<(const Optional<T>& rhs) const
    {
        return !rhs ? false : (!bool(*this) ? true : (*(*this) < (*rhs)));
    }

    bool operator!=(const Optional<T>& rhs)
    {
        return !(*this == rhs);
    }

private:
    template<typename... Args>
    void create(Args&&... args)
    {
        new (&m_data) T(std::forward<Args>(args)...);
        m_isInit = true;
    }

    void destroy()
    {
        if (m_isInit)
        {
            m_isInit = false;
            ((T*)(&m_data))->~T();
        }
    }

    void assign(const Optional& other)
    {
        if (other.isInit())
        {
            copy(other.m_data);
            m_isInit = true;
        }
        else
        {
            destroy();
        }
    }

    void assign(Optional&& other)
    {
        if (other.isInit())
        {
            move(std::move(other.m_data));
            m_isInit = true;
            other.destroy();
        }
        else
        {
            destroy();
        }
    }

    void move(data_t&& value)
    {
        destroy();
        new (&m_data) T(std::move(*((T*)(&value))));
    }

    void copy(const data_t& value)
    {
        destroy();
        new (&m_data) T(*((T*)(&value)));
    }

private:
    bool m_isInit = false;
    data_t m_data;
};

#endif
