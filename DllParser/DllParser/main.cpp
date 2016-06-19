/************************************************
 * 该例程讲解用C++11来实现一个通用的动态库解析器
 * 使用到的C++11特性有：
 * 1.可变参数模板类
 * 2.智能指针
 * 3.函数相关std::function
 * 4.using关键字
 * 5.判断函数的返回值类型std::result_of
 * 6.完美转发std::forward
************************************************/
#include "DllParser.hpp"

int main()
{
    std::string dllFilePath = "../Caculate/libcac.so";

    /* DllParserPtr dllParser(new DllParser); */
    DllParser parser;
    bool ret = parser.load(dllFilePath);
    if (!ret)
    {
        return 1;
    }

    int a = 20;
    int b = 10;

    try
    {
        auto addRet = parser.excecuteFunction<int(int, int)>("add", a, b);
        std::cout << "a + b = " << addRet << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    try
    {
        auto subRet = parser.excecuteFunction<int(int, int)>("sub", a, b);
        std::cout << "a - b = " << subRet << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::string str = "Hello C++11";
    try
    {
        parser.excecuteFunction<void(std::string)>("print", str);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

