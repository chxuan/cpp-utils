/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月07日 星期一 21时10分35秒
 ************************************************************************/

#include <iostream>
#include <string>
#include "LogWrapper.h"

int main()
{
    int a = 1;
    int b = 2;
    std::string str = "Hello world";

    // C风格
    logError("Error log");
    logWarn("Warn log");
    logInfo("a + b = %d", a + b);

    // C++风格
    logError() << "Hello world";
    logWarn() << "Hello world";
    logDebug() << "message: " << str;

    return 0;
}
