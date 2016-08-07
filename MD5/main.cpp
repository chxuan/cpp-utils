#include <iostream>
#include "md5.h"

int main()
{
    std::string str = "123";
    std::cout << md5(str) << std::endl;
    std::cout << md5("中国") << std::endl;

    return 0;
}
