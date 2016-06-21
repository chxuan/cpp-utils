/************************************************
 *该例程讲解base64接口的调用
************************************************/
#include <iostream>
#include <string>
#include "Base64.hpp"

int main()
{
    char buf[20] = "Hello world!";
    std::string base64Str = Base64::encode(buf, sizeof(buf)); 
    std::cout << base64Str << std::endl;
    std::string buf2 = Base64::decode(base64Str);
    std::cout << buf2 << std::endl;
    return 0;
}
