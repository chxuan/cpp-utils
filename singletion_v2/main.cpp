#include "singletion.h"
#include <iostream>

class test
{
public:
    void print()
    {
        std::cout << "hello world" << std::endl;
    }

    test()
    {
        std::cout << "test" << std::endl;
    }

    ~test()
    {
        std::cout << "~test" << std::endl;
    }
};

int main()
{
    singletion<test>::get_instance()->print();
    singletion<test>::get_instance()->print();
    return 0;
}
