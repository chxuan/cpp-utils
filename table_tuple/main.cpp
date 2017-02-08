#include <iostream>
#include <string>
#include "table_tuple.hpp"

int main()
{
    table_tuple<int, std::string, std::string> test("id", "name", "address");
    for (int i = 0; i < 1000000; ++i)
    {
        test.insert(1, "Jack", "ChengDu");
    }
    /* test.print(); */
    return 0;
}
