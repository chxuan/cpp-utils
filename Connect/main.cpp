/************************************************
 * 该例程讲解用C++11来实现Qt的信号槽机制
 * 使用到的C++11特性有：
 * 1.可变参数模板类
 * 2.智能指针
 * 3.函数相关std::function、std::bind
 * 4.using关键字
 * 5.完美转发std::forward
************************************************/
#include "Connect.hpp"
#include <iostream>
#include <string>

class A
{
public:
    void start()
    {
        emit m_s1();
        emit m_s2("Hello C++11");
        emit m_s3(100, "Hello C++11");
    }

signals:
    Signal<> m_s1;  // 不带参数的信号
    Signal<std::string> m_s2;
    Signal<int, std::string> m_s3;
};

class B
{
public slots:
    void func1()
    {
        std::cout << "func1" << std::endl;
    }

    void func2(const std::string& str)
    {
        std::cout << str << std::endl;
    }

    void func3(int n, const std::string& str)
    {
        std::cout << n << " " << str << std::endl;
    }
};

void func(const std::string& str)
{
    std::cout << "func " << str << std::endl;
}

int main()
{
    A a;
    B b;

    // 信号与槽绑定
    connect(&a, m_s1, std::bind(&B::func1, &b));
    connect(&a, m_s2, std::bind(&B::func2, &b, std::placeholders::_1));
    connect(&a, m_s3, std::bind(&B::func3, &b, std::placeholders::_1, std::placeholders::_2));
    connect(&a, m_s2, std::bind(func, std::placeholders::_1));
    connect(&a, m_s2, [](const std::string& str)
            {
                std::cout << "lambda str: " << str << std::endl;
            });

    a.start();

    return 0;
}

