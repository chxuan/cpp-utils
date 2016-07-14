#include <iostream>
#include "lexical_cast.hpp"

int main()
{
    std::string str = "1000";
    std::cout << lexical_cast<int>(str) << std::endl;
    return 0;
}
