#include <iostream>
#include <typeinfo>
#include "Args.hpp"

int main()
{
    std::cout << Sum<int, double, short>::value << std::endl;
    std::cout << typeid(MakeIndexes<3>::type).name() << std::endl;
    return 0;
}
