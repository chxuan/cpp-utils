#include <iostream>
#include <type_traits>

struct A
{
    A(int a, int b)
    {
        m_avg = (a + b) / 2;
    }

    int m_avg;
};

using Aligned_A = std::aligned_storage<sizeof(A), alignof(A)>::type;

int main()
{
    Aligned_A a, b;
    new (&a) A(2, 2);
    b = a;
    std::cout << reinterpret_cast<A&>(b).m_avg << std::endl;
    return 0;
}
