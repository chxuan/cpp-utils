#include <iostream>
#include <string>
#include "Any.hpp"

int main()
{
    Any n;
    std::cout << n.isNull() << std::endl;
    std::string str = "Hello";
    n = str;

    try
    {
        n.anyCast<int>();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    Any n1 = 1;
    std::cout << n1.is<int>() << std::endl;

    return 0;
}
