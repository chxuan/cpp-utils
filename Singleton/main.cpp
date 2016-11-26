/************************************************
 * 该例程讲解用C++11来实现一个通用的单列类
************************************************/
#include <iostream>
#include <string>
#include "Singleton.hpp"

class A
{
    DEFINE_SINGLETON(A);
public:
    A(const std::string& str)
        : m_str(str)
    {
        // Do nothing 
    }

    void print()
    {
        std::cout << m_str << std::endl;
    }

    std::string m_str = "nihao";
};

class B
{
    DEFINE_SINGLETON(B);
public:
    B() = default;
    void print()
    {
        std::cout << "Hello world" << std::endl;
    }
};

int main()
{
    std::string str = "Hello C++11";
    A::singleton::get_instance(str).print();
    B::singleton::get_instance().print();
    return 0;
}
