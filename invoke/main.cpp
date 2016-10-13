#include <iostream>
#include "invoke.hpp"

int add(int a, int b)
{
    return a + b;
}

int main()
{
    std::tuple<int, int> t = std::make_tuple(1, 2);
    std::cout << invoke(add, t) << std::endl;
    return 0;
}

