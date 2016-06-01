#include <dlfcn.h>
#include <iostream>
#include <string>

int main()
{
    std::string dllFilePath = "libcac.so";
    void* handle = dlopen(dllFilePath.c_str(), RTLD_NOW);
    if (handle == nullptr)
    {
        std::cout << "Open dll: " << dllFilePath << " failed, error: " << dlerror() << std::endl;
        return -1;
    }

    int a = 20;
    int b = 10;

    using OnFunc = int(*)(int, int);
    OnFunc func;

    func = (OnFunc)dlsym(handle, "add");
    std::cout << "a + b = " << func(a, b) << std::endl;

    func = (OnFunc)dlsym(handle, "sub");
    std::cout << "a - b = " << func(a, b) << std::endl;

    int ret = dlclose(handle);
    if (ret != 0)
    {
        std::cout << "Close dll: " << dllFilePath << " failed, error: " << dlerror() << std::endl;
        return -1;
    }

    return 0;
}

