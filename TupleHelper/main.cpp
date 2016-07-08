#include <iostream>
#include <string>
#include "TupleHelper.hpp"

int main()
{
    std::tuple<int, short, double, char> tp = std::make_tuple(1, 2, 3, 'a');
    printTuple(tp);
    printTuple(std::forward_as_tuple("Hello", "world"));
    return 0;
}
