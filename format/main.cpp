#include <stdio.h>
#include <iostream>
#include "format.h"
#include "timer.hpp"
#include "fmt/fmt.h"

int main()
{
    /* std::string text = "a = {}, b = {}"; */
    /* std::cout << format(text, 10.23, 200) << std::endl; */

    /* double a = 3.1234; */
    /* std::cout << format("a:{}, b:{}", 10.23, a) << std::endl; */

    /* std::string str = "hello world"; */
    /* std::cout << format("a:{}, b:{}", 10.23, str) << std::endl; */
    /* std::cout << format("a:{}, b:{}", 10.23, "hello") << std::endl; */
    /* std::cout << format("hello") << std::endl; */

    /* char buf[4096] = {"\0"}; */
    /* sprintf(buf, "%lf:%d:%lf:%s:%d:%c:\n", 1.234, 42, 3.13, "str", 1000, 'X'); */
    /* std::cout << buf; */
    /* std::cout << format("你好我是中国人你好我是忠人你好我是忠人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人{}:{}:{}:{}:{}:{}:%\n", 1.234, 42, 3.13, "str", 1000, 'X'); */
    /* std::cout << fmt::format("{}:{}:{}:{}:{}:{}:%\n", 1.234, 42, 3.13, "str", 1000, 'X'); */
    /* return 0; */

    timer t;
    for (int i = 1; i <= 2000000; ++i)
    {
        char buf[4096] = {"\0"};
        sprintf(buf, "11111111111111111111111111111111111111111111111111111111111111111111111你好我是中国人你好我是忠人你好我是忠人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人%lf:%d:%lf:%s:%d:%c:\n", 1.234, 42, 3.13, "str", 1000, 'X');
    }

    std::cout << "sprintf耗时:" << t.elapsed() << "ms" << std::endl;

    t.reset();

    for (int i = 1; i <= 2000000; ++i)
    {
        format("11111111111111111111111111111111111111111111111111111111111111111111111你好我是中国人你好我是忠人你好我是忠人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人{}:{}:{}:{}:{}:{}:%\n", 1.234, 42, 3.13, "str", 1000, 'X');
    }

    std::cout << "my format耗时:" << t.elapsed() << "ms" << std::endl;

    t.reset();

    for (int i = 1; i <= 2000000; ++i)
    {
        fmt::format("11111111111111111111111111111111111111111111111111111111111111111111111你好我是中国人你好我是忠人你好我是忠人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人你好我是中国人{}:{}:{}:{}:{}:{}:%\n", 1.234, 42, 3.13, "str", 1000, 'X');
    }

    std::cout << "fmt::format耗时:" << t.elapsed() << "ms" << std::endl;

    return 0;
}
