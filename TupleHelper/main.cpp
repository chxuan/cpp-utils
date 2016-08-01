#include <iostream>
#include <string>
#include "TuplePrinter.hpp"

int main()
{
    std::cout << "******TuplePrinter*********" << std::endl;
    std::tuple<int, short, double, char> tp = std::make_tuple(1, 2, 3, 'a');
    printTuple(tp);
    printTuple(std::forward_as_tuple("Hello", "world"));
    return 0;
}
