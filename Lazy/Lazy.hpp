#ifndef _LAZY_H
#define _LAZY_H

#include <iostream>
#include <functional>
#include <boost/optional.hpp>

template<typename R>
class Lazy
{
public:
    template<typename Function, typename... Args>
    Lazy(Function&& func, Args&&... args)
    {
        m_func = [&func, &args...]{ return func(std::forward<Args>(args)...); };
    }

    R& value()
    {
        m_value = m_func();
        return *m_value;
    }

private:
    std::function<R()> m_func;
    boost::optional<R> m_value;
};

template<typename Function, typename... Args>
Lazy<typename std::result_of<Function(Args...)>::type> lazy(Function&& func, Args&&... args)
{
    return Lazy<typename std::result_of<Function(Args...)>::type>(std::forward<Function>(func), std::forward<Args>(args)...);
}

#endif
