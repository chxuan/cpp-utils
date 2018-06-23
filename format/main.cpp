#include <iostream>
#include "format.h"

int main()
{
    std::string text = "a = {}, b = {}";
    std::cout << format(text, 10.23, 200) << std::endl;

    double a = 3.1234;
    std::cout << format("a:{}, b:{}", 10.23, a) << std::endl;

    std::string str = "hello world";
    std::cout << format("a:{}, b:{}", 10.23, str) << std::endl;
    std::cout << format("a:{}, b:{}", 10.23, "hello") << std::endl;

    return 0;
}
