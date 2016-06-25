#include <iostream>
#include <string>
#include "FunctionTraits.hpp"

template<typename T>
void printType()
{
    std::cout << typeid(T).name() << std::endl;
}

float (*func)(std::string, int);
float func2(const std::string& str, int b)
{
    return static_cast<float>(str.size() + b);
}

struct AA
{
    int func(int a, int b) volatile {return a + b;}
    int operator()(int) const {return 0;}
};

int main()
{
    std::function<int(int)> f = [](int a){return a;};

    printType<FunctionTraits<std::function<int(int)>>::functionType>();
    printType<FunctionTraits<std::function<int(int)>>::args<0>::type>();
    printType<FunctionTraits<std::function<int(int)>>::returnType>();
    printType<FunctionTraits<decltype(f)>::functionType>();
    printType<FunctionTraits<decltype(func)>::functionType>();
    printType<FunctionTraits<decltype(func2)>::functionType>();

    printType<FunctionTraits<AA>::functionType>();
    printType<decltype(&AA::func)>();
    printType<FunctionTraits<decltype(&AA::func)>::functionType>();

    return 0;
}
