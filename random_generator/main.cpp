#include <iostream>
#include "random_generator.h"

int main()
{
    for (int i = 1; i < 10; ++i)
    {
        random_generator random;
        std::cout << random.randint(1, 10) << std::endl; 
    }

    std::cout << "---------------" << std::endl;
    for (int i = 1; i < 10; ++i)
    {
        random_generator random;
        std::cout << random.randreal(1, 2) << std::endl;
    }

    return 0;
}

