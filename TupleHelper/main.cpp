#include <iostream>
#include <string>
#include "TuplePrinter.hpp"
#include "TupleGet.hpp"

int main()
{
    std::cout << "******TuplePrinter*********" << std::endl;
    std::tuple<int, short, double, char> tp = std::make_tuple(1, 2, 3, 'a');
    printTuple(tp);
    printTuple(std::forward_as_tuple("Hello", "world"));

    std::cout << "******std::cout*********" << std::endl;
    std::cout << tp << std::endl;

    std::cout << "******TupleGet*********" << std::endl;
    auto a = getElementByType<double>(tp);
    std::cout << "double: " << a << std::endl;
    auto b = getElementByType<char>(tp);
    std::cout << "char: " << b << std::endl;


    std::cout << "******std::array to std::tuple*********" << std::endl;
    std::array<int, 4> arr { 1, 2, 3, 4 };
    std::cout << array2tuple(arr) << std::endl;

    return 0;
}
