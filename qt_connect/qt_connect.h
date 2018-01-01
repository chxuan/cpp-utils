/**
 * @file qt_connect.h
 * @brief 仿Qt的信号槽机制，用于类之间的解耦
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-11-25
 */
#pragma once

#include <vector>
#include <memory>
#include <functional>

#define emit
#define slots
#define qt_connect(qt_sig, qt_slt) (qt_sig.bind(qt_slt))

template<typename... Args>
class qt_slot
{
public:
    using func_t = std::function<void(const Args&...)>;
    qt_slot(const func_t& func) : func_(func) {}

    void exec(const Args&... args)
    {
        func_(args...);
    }

private:
    func_t func_;
};

template<typename... Args>
class qt_signal
{
public:
    using slot_ptr = std::shared_ptr<qt_slot<Args...>>; 
    using func_t = std::function<void(const Args&...)>;

    void bind(const func_t& func)
    {
        auto s = std::make_shared<qt_slot<Args...>>(func);
        slots_.emplace_back(s);
    }

    void operator()(const Args&... args)
    {
        for (auto& s : slots_)
        {
            s->exec(args...);
        }
    }

private:
    std::vector<slot_ptr> slots_;
};

