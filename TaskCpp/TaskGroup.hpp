#ifndef _TASKGROUP_H
#define _TASKGROUP_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/variant.hpp>
#include <boost/any.hpp>
#include "Task.hpp"

namespace taskcpp
{

boost::any Func;

template<typename T>
void futureGet()
{
    boost::any_cast<std::shared_future<T>>(Func).get();
}

class Visitor : public boost::static_visitor<>
{
public:
    template<typename T>
    void operator()(const T&) const
    {
        futureGet<T>(); 
    }
};

class TaskGroup
{
public:
    void run(Task<void()>& task)
    {
        m_voidGroup.emplace_back(task.run());
    }

    void run(Task<void()>&& task)
    {
        m_voidGroup.emplace_back(task.run());
    }

    template<typename F>
    void run(F&& f)
    {
        run(Task<typename std::result_of<F()>::type()>(std::forward<F>(f)));
    }

    template<typename R, typename = typename std::enable_if<!std::is_same<R, void>::value>::type>
    void run(Task<R()>& task)
    {
        m_group.insert(std::make_pair<Variant, boost::any>(R(), task.run()));
    }

    template<typename R, typename = typename std::enable_if<!std::is_same<R, void>::value>::type>
    void run(Task<R()>&& task)
    {
        m_group.insert(std::make_pair<Variant, boost::any>(R(), task.run()));
    }

    template<typename F, typename... Funcs>
    void run(F&& first, Funcs&&... rest)
    {
        run(std::forward<F>(first));
        run(std::forward<Funcs>(rest)...);
    }

    void wait()
    {
        for (auto& iter : m_voidGroup)
        {
            iter.get();
        }

        for (auto iter = m_group.begin(); iter != m_group.end(); ++iter)
        {
            Func = iter->second;
            boost::apply_visitor(Visitor(), iter->first);
        }
    }

private:
    std::vector<std::shared_future<void>> m_voidGroup; 
    using Variant = boost::variant<int, double, std::string, short, unsigned int>;
    std::multimap<Variant, boost::any> m_group;
};

};

#endif
