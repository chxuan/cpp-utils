#include <iostream>
#include <string>
#include "Meta.hpp"

struct Person
{
    std::string name;
    int age;

    META(name, age)
};

template<typename T>
void func(T& t)
{
    auto ret = t.meta();
    std::cout << "Hello world" << std::endl;
}

int main()
{
    Person p {"Jack", 10};
    func(p);
    return 0;
}
