/************************************************
 * 该例程讲解用C++11来实现一个通用的单列类
************************************************/
#include <iostream>
#include <string>
#include "Singleton.hpp"

struct A
{
    A(const std::string& str)
        : m_str(str)
    {
        // Do nothing 
    }

    void print()
    {
        std::cout << m_str << std::endl;
    }

    std::string m_str;
};

struct B
{
    void print()
    {
        std::cout << "Hello world" << std::endl;
    }
};

int main()
{
    std::string str = "Hello C++11";
    Singleton<A>::getInstance(str).print();
    Singleton<A>::getInstance(str).print();
    Singleton<B>::getInstance().print();
    Singleton<B>::getInstance().print();
    return 0;
}
