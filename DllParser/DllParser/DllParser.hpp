#ifndef _DLLPARSER_H
#define _DLLPARSER_H

#include <dlfcn.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class DllParser
{
public:
    ~DllParser()
    {
        unload();
    }

    bool load(const std::string& dllFilePath)
    {
        m_handle = dlopen(dllFilePath.c_str(), RTLD_NOW);
        if (m_handle == nullptr)
        {
            std::cout << "Open dll failed, error: " << dlerror() << std::endl;
            return false;
        }

        return true;
    }

    bool unload()
    {
        if (m_handle == nullptr)
        {
            return true;
        }

        int ret = dlclose(m_handle);
        m_handle = nullptr;
        if (ret != 0)
        {
            std::cout << "Close dll failed, error: " << dlerror() << std::endl;
            return false;
        }

        return true;
    }

    template<typename T>
    std::function<T> getFunction(const std::string& funcName)
    {
        auto iter = m_funcMap.find(funcName);
        if (iter == m_funcMap.end())
        {
            void* addr = dlsym(m_handle, funcName.c_str());
            if (addr == nullptr)
            {
                std::cout << "func is nullptr, error: " << dlerror() << std::endl;
                return nullptr;
            }

            m_funcMap.emplace(funcName, addr);
            return std::function<T>(reinterpret_cast<T*>(addr));
        }
        
        return std::function<T>(reinterpret_cast<T*>(iter->second));
    }

    template<typename T, typename... Args>
    typename std::result_of<std::function<T>(Args...)>::type excecuteFunction(const std::string& funcName, Args&&... args)
    {
        auto func = getFunction<T>(funcName);
        if (func == nullptr)
        {
            std::string str = "Can not find this function: " + funcName;
            throw std::runtime_error(str);
        }

        return func(std::forward<Args>(args)...);
    }

private:
    void* m_handle = nullptr;
    std::unordered_map<std::string, void*> m_funcMap;
};

#endif
