#include "FunctionTraits.hpp"
#include <iostream>
#if defined(__GNUC__)
#include <cxxabi.h>
#endif
#include <string>
#include <typeinfo>

template<typename T>
void printType()
{
#if defined(__GNUC__)
    std::cout << abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr) << std::endl;
#else    
    std::cout << typeid(T).name() << std::endl;
#endif    
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
    std::cout << "count: " << FunctionTraits<std::function<int(int)>>::arity << std::endl;
    
    printType<FunctionTraits<decltype(f)>::functionType>();
    printType<FunctionTraits<decltype(func)>::functionType>();
    printType<FunctionTraits<decltype(func2)>::functionType>();

    printType<FunctionTraits<AA>::functionType>();
    printType<decltype(&AA::func)>();
    printType<FunctionTraits<decltype(&AA::func)>::functionType>();

    return 0;
}
