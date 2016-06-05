#include "ScopeGuard.hpp"
#include <iostream>
#include <functional>

int main()
{
    std::function<void()> func = []
    {
        std::cout << "Cleanup from unnormal exit" << std::endl;
    };

    {
        auto ret = makeGuard(func);
        ret.dismiss();
    }

    {
        makeGuard(func);
    }

    return 0;
}
