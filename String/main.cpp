#include <iostream>
#include "StringUtil.hpp"
#include "Format.hpp"

int main()
{
    std::string str = "Hello world";
    std::cout << StringUtil::trimLeft(str, "Hello") << std::endl;
    std::cout << StringUtil::trimRight(str, "world") << std::endl;
    str = "  nihao ";
    std::cout << StringUtil::trim(str) << std::endl;
    std::cout << StringUtil::toUpper(str) << std::endl;
    std::cout << StringUtil::toLower(StringUtil::toUpper(str)) << std::endl;
    str = "Hello world";
    std::cout << StringUtil::startsWith(str, "Hello") << std::endl;
    std::cout << StringUtil::endsWith(str, "a") << std::endl;
    std::vector<std::string> result = StringUtil::split(str, " ");
    for (auto& iter : result)
    {
        std::cout << iter << std::endl;
    }

    try
    {
        std::string str = "a = {0}, b = {1}";
        std::cout << format(const_cast<char*>(str.c_str()), 10.23, 200) << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
