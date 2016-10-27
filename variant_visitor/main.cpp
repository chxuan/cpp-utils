#include <iostream>
#include <string>
#include <boost/variant.hpp>
#include "variant_visitor.hpp"

int main()
{
    auto visitor = make_visitor
    (
        [](int& i) { std::cout << i << std::endl; },
        [](std::string& i) { std::cout << i << std::endl; }
    );
    boost::variant<int, std::string> v;
    v = "Hello world";
    boost::apply_visitor(visitor, v);
    v = 100;
    boost::apply_visitor(visitor, v);

    return 0;
}
