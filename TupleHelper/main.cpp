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

    std::cout << "******TupleGet*********" << std::endl;
    auto a = getElementByType<double>(tp);
    std::cout << "double: " << a << std::endl;
    auto b = getElementByType<char>(tp);
    std::cout << "char: " << b << std::endl;

    return 0;
}
