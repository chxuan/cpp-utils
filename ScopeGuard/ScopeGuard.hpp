#ifndef _SCOPEGUARD_H
#define _SCOPEGUARD_H

#include <iostream>

template<typename T>
class ScopeGuard
{
public:
    ScopeGuard() = default;
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    explicit ScopeGuard(T&& func) : m_func(std::move(func)) {}
    explicit ScopeGuard(const T& func) : m_func(func) {}

    ~ScopeGuard()
    {
        if (!m_dismiss && m_func != nullptr)
        {
            m_func();
        }
    }

    ScopeGuard(ScopeGuard&& other)
        : m_func(std::move(other.m_func))
    {
        other.dismiss();
    }

    void dismiss()
    {
        m_dismiss = true;
    }

private:
    T m_func = nullptr;
    bool m_dismiss = false;
};

template<typename T>
ScopeGuard<typename std::decay<T>::type> makeGuard(T&& func)
{
    return ScopeGuard<typename std::decay<T>::type>(std::forward<T>(func));
}

#endif
