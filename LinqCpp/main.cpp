#include <iostream>
#include <string>
#include <vector>
#include "LinqCpp.hpp"

int main()
{
    std::vector<int> vec { 1, 2, 3, 4 };
    auto range = from(vec).select([](int i){ return i + 2; });
    for (auto iter : range)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    auto ret = from(vec).select([](int i){ return i + 2; }).where([](int i){ return i > 2; }).max();
    std::cout << "max: " << ret << std::endl;

    auto ret2 = from(vec).sum();
    std::cout << "sum: " << ret2 << std::endl;
    return 0;
}
