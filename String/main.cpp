#include <iostream>
#include "String.hpp"

int main()
{
    std::string str = "Hello world";
    std::cout << String::trimLeft(str, "Hello") << std::endl;
    std::cout << String::trimRight(str, "world") << std::endl;
    str = "  nihao ";
    std::cout << String::trim(str) << std::endl;
    std::cout << String::toUpper(str) << std::endl;
    std::cout << String::toLower(String::toUpper(str)) << std::endl;
    str = "Hello world";
    std::cout << String::startsWith(str, "Hello") << std::endl;
    std::cout << String::endsWith(str, "a") << std::endl;
    std::vector<std::string> result = String::split(str, " ");
    for (auto& iter : result)
    {
        std::cout << iter << std::endl;
    }
    return 0;
}
