#include <iostream>
#include "Range.hpp"

int main()
{
    std::cout << "range(5): ";
    for (int i : range(5))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range(2, 6): ";
    for (int i : range(2, 6))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range(10.5, 15.5): ";
    for (int i : range(10.5, 15.5))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range(35, 27, -1): ";
    for (int i : range(35, 27, -1))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range(2, 8, 0.5): ";
    for (float i : range(2, 8, 0.5))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range(8, 7, -0.1): ";
    for (auto i : range(8, 7, -0.1))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "range('a', 'z'): ";
    for (auto i : range('a', 'z'))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

