#include <iostream>
#include "ObjectPool.hpp"

class A
{
public:
    void print()
    {
        std::cout << "Hello world" << std::endl;
    }
};

int main()
{
    ObjectPool<A> pool;
    pool.add(std::unique_ptr<A>(new A()));
    pool.add(std::unique_ptr<A>(new A()));
    std::cout << "Object pool size: " << pool.size() << std::endl;

    {
        auto a = pool.get();
        a->print();
        pool.get();
        std::cout << "Object pool size: " << pool.size() << std::endl;
    }

    std::cout << "Object pool size: " << pool.size() << std::endl;

    return 0;
}
