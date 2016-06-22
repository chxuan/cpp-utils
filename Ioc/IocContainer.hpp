#ifndef _IOCCONTAINER_H
#define _IOCCONTAINER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

template<typename T>
class IocContainer
{
public:
    template<class Drived>
    void registerType(const std::string& key)
    {
        std::function<T*()> func = []{return new Drived();};
        registerType(key, func);
    }

    std::shared_ptr<T> resolveShared(const std::string& key)
    {
        T* t = resolve(key);
        return std::shared_ptr<T>(t);
    }

private:
    void registerType(const std::string& key, const std::function<T*()>& func)
    {
        auto iter = m_funcMap.find(key);
        if (iter != m_funcMap.end())
        {
            std::string errorString = key + " key has already exist.";
            throw std::invalid_argument(errorString);
        }

        m_funcMap.emplace(key, func);
    }

    T* resolve(const std::string& key)
    {
        auto iter = m_funcMap.find(key);
        if (iter != m_funcMap.end())
        {
            return (iter->second)();
        }

        return nullptr;
    }

private:
    std::unordered_map<std::string, std::function<T*()>> m_funcMap;
};

#endif
