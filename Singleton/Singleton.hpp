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
    static T& get_instance(Args&&... args)
    {
        static T t {std::forward<Args>(args)...};
        return t;
    }
};

#define DEFINE_SINGLETON(class_name) \
public: \
friend class Singleton<class_name>; \
using singleton = Singleton<class_name>; \
private: \
virtual ~class_name() {} \
class_name(const class_name&) = delete; \
class_name& operator=(const class_name&) = delete; \
public: 

#endif
