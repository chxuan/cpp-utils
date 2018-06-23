#include <iostream>
#include "lexical_cast.h"

int main()
{
    std::string str = "1000";
    int n = 200;
    std::cout << lexical_cast<int>(str) << std::endl;
    std::cout << lexical_cast<std::string>(n) << std::endl;
    std::cout << lexical_cast<bool>(n) << std::endl;
    std::cout << lexical_cast<bool>(-1) << std::endl;

    std::cout << lexical_cast<std::string>(str) << std::endl;
    std::cout << lexical_cast<std::string>("hello") << std::endl;
    return 0;
}
