#include <iostream>
#include <string>
#include "table_tuple.hpp"

int main()
{
    table_tuple<int, std::string> test("id", "name");
    return 0;
}
