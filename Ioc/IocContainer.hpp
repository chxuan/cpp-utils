#ifndef _IOCCONTAINER_H
#define _IOCCONTAINER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "Any.hpp"

class IocContainer
{
public:
    IocContainer() = default;
    IocContainer(const IocContainer&) = delete;
    IocContainer& operator=(const IocContainer&) = delete;

    template<typename T, typename Depend, typename... Args>
    typename std::enable_if<!std::is_base_of<T, Depend>::value>::type registerType(const std::string& key)
    {
        // 通过闭包擦除参数类型
        std::function<T*(Args...)> func = [](Args... args){return new T(new Depend(args...));};
        registerType(key, func);
    }

    template<typename T, typename Depend, typename... Args>
    typename std::enable_if<std::is_base_of<T, Depend>::value>::type registerType(const std::string& key)
    {
        // 通过闭包擦除参数类型
        std::function<T*(Args...)> func = [](Args... args){return new Depend(args...);};
        registerType(key, func);
    }

    template<typename T, typename... Args>
    void registerSimple(const std::string& key)
    {
        std::function<T*(Args...)> func = [](Args... args){return new T(args...);};
        registerType(key, func);
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> resolveShared(const std::string& key, Args... args)
    {
        T* t = resolve<T>(key, args...);
        return std::shared_ptr<T>(t);
    }

    template<typename T, typename... Args>
    T* resolve(const std::string& key, Args... args)
    {
        auto iter = m_creatorMap.find(key);
        if (iter != m_creatorMap.end())
        {
            Any resolver = iter->second;
            std::function<T*(Args...)> func = resolver.anyCast<std::function<T*(Args...)>>();
            return func(args...);
        }

        return nullptr;
    }

private:
    void registerType(const std::string& key, Any constructor)
    {
        auto iter = m_creatorMap.find(key);
        if (iter != m_creatorMap.end())
        {
            std::string errorString = key + " key has already exist.";
            throw std::invalid_argument(errorString);
        }

        // 通过Any擦除不同类型的构造器
        m_creatorMap.emplace(key, constructor);
    }

private:
    std::unordered_map<std::string, Any> m_creatorMap;
};

#endif
