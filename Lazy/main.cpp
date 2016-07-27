#include <iostream>
#include "Lazy.hpp"

int main()
{
    Lazy<int> lazyer = lazy([]{ return 10; });
    std::cout << lazyer.value() << std::endl;

    std::function<int(int)> f = [](int i){ return i; };
    auto lazyer2 = lazy(f, 100);
    std::cout << lazyer2.value() << std::endl;
    return 0;
}

