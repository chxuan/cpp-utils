#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>

template<typename T>
class Singleton
{
public:
    Singleton() = delete;
    virtual ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    template<typename... Args>
    static T& getInstance(Args&&... args)
    {
        static T t(std::forward<Args>(args)...);
        return t;
    }
};

#endif
