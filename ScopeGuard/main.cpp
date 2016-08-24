/************************************************
 * 该例程讲解用C++11来实现一个ScopeGuard类
************************************************/
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
        // 正常退出
        auto ret = makeGuard(func);
        ret.dismiss();
    }

    {
        // 非正常退出，调用func函数
        auto ret = makeGuard(func);
    }

    return 0;
}
