#include <iostream>
#include "Variant.hpp"

int main()
{
    std::cout << Contains<int, short, double>::value << std::endl;
    return 0;
}
