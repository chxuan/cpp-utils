#include <iostream>
#include "DateTime.hpp"

int main()
{
    std::string timeStr = DateTime::convert<std::string>(time(nullptr));
    std::cout << timeStr << std::endl;
    std::cout << DateTime::convert<time_t>(timeStr) << std::endl;
    std::cout << DateTime::currentTime() << std::endl << std::endl;

    return 0;
}
