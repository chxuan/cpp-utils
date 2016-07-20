#ifndef _TASKCPP_H
#define _TASKCPP_H

#include <functional>
#include <future>
#include <type_traits>

namespace taskcpp
{

template<typename T>
class Task;

template<typename R, typename... ArgsType>
class Task<R(ArgsType...)>
{
public:
    Task(std::function<R(ArgsType...)>&& func) : m_func(std::move(func)) {}
    Task(const std::function<R(ArgsType...)>& func) : m_func(func) {}

    void wait()
    {
        std::async(m_func).wait();
    }

    template<typename... Args>
    R get(Args&&... args)
    {
        return std::async(m_func, std::forward<Args>(args)...).get();
    }

    std::shared_future<R> run()
    {
        return std::async(m_func);
    }

#if 0
    template<typename F>
    auto then(F&& f)->Task<typename std::result_of<F(R)>::type(ArgsType...)>
    {
        using ReturnType = typename std::result_of<F(int)>::type;
        auto func = std::move(m_func);
        return Task<ReturnType(ArgsType...)>([func, &f](ArgsType&&... args)
        {
            std::future<int> ret = std::async(func, std::forward<ArgsType>(args)...);
            return std::async(f, ret.get()).get();
        });
    }
#endif

private:
    std::function<R(ArgsType...)> m_func;
};

};

#endif
