#include <iostream>
#include <string>
#include "Optional.hpp"

struct A
{
    A(int a, int b) : m_a(a), m_b(b) {}

    int m_a;
    int m_b;

    void print()
    {
        std::cout << "Hello world" << std::endl;
    }
};

int main()
{
    Optional<std::string> a("ok");
    if (a)
    {
        std::cout << *a << std::endl;
    }

    Optional<std::string> b("ok");
    std::cout << (a == b) << std::endl;

    Optional<A> op;
    op.emplace(1, 2);
    A op2(2, 3);
    if (op)
    {
        op2 = *op;
        std::cout << op2.m_a << ", " << op2.m_b << std::endl;
        op->print();
    }
    return 0;
}
