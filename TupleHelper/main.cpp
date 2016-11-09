#include <iostream>
#include <string>
#include "tuple_helper.hpp"

int add(int a, int b)
{
    return a + b;
}

struct person
{
    int age = 0;
    std::string name;
};

int main()
{
    std::cout << "******tuple_printer*********" << std::endl;
    std::tuple<int, short, double, char> tp = std::make_tuple(1, 2, 3, 'a');
    print_tuple(tp);
    print_tuple(std::forward_as_tuple("Hello", "world"));

    std::cout << "******std::cout*********" << std::endl;
    std::cout << tp << std::endl;

    std::cout << "******get_element_by_type*********" << std::endl;
    auto a = get_element_by_type<double>(tp);
    std::cout << "double: " << a << std::endl;
    auto b = get_element_by_type<char>(tp);
    std::cout << "char: " << b << std::endl;


    std::cout << "******std::array to std::tuple*********" << std::endl;
    std::array<int, 4> arr { 1, 2, 3, 4 };
    std::cout << array2tuple(arr) << std::endl;

    std::cout << "******std::tuple invoke*********" << std::endl;
    std::tuple<int, int> t = std::make_tuple(1, 2);
    std::cout << invoke(add, t) << std::endl;

    std::cout << "******make_from_tuple*********" << std::endl;
    std::tuple<int, std::string> p = std::make_tuple(20, "Jack");
    auto pp = make_from_tuple<person>(p);
    std::cout << pp.age << ", " << pp.name << std::endl;

    return 0;
}
