#include "DllParser.hpp"

int main()
{
    std::string dllFilePath = "../Caculate/libcac.so";

    DllParserPtr dllParser(new DllParser);
    bool ret = dllParser->load(dllFilePath);
    if (!ret)
    {
        return 1;
    }

    int a = 20;
    int b = 10;

    try
    {
        auto addRet = dllParser->excecuteFunction<int(int, int)>("add", a, b);
        std::cout << "a + b = " << addRet << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    try
    {
        auto subRet = dllParser->excecuteFunction<int(int, int)>("sub", a, b);
        std::cout << "a - b = " << subRet << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

