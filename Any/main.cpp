#include <iostream>
#include <string>
#include <vector>
#include "Any.hpp"

int main()
{
    Any n;
    auto r = n.isNull();
    std::cout << "r: " << r << std::endl;
    /* std::string str = "Hello"; */
    /* n = str; */

    return 0;
}
