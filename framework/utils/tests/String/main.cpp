/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月28日 星期六 17时52分52秒
 ************************************************************************/

#include <iostream>
#include "Utils.h"

int main()
{
    /************int32 uint32 int64 uint64 float double to string test*********/

    std::cout << "#################to string#############################" << std::endl;
    int a = 123;
    std::string astr = utils::String::int32ToString(a);
    std::cout << "int32 to string: " << astr << std::endl;

    unsigned int b = 123;
    std::string bstr = utils::String::uint32ToString(b);
    std::cout << "uint32 to string: " << bstr << std::endl;

    long long c = 123;
    std::string cstr = utils::String::int64ToString(c);
    std::cout << "int64 to string: " << cstr << std::endl;

    unsigned long long d = 123;
    std::string dstr = utils::String::uint64ToString(d);
    std::cout << "uint64 to string: " << dstr << std::endl;

    float e = 1.23;
    std::string estr = utils::String::floatToString(e);
    std::cout << "float to string: " << estr << std::endl;

    double f = 1.23;
    std::string fstr = utils::String::doubleToString(f);
    std::cout << "double to string: " << fstr << std::endl;


    /************string to int32 uint32 int64 uint64 float double test*********/

    std::cout << "#################string to#############################" << std::endl;
    astr = "1234a";
    bool ok = utils::String::stringToInt32(astr, a);
    if (ok)
    {
        std::cout << "string to int32: " << a << std::endl;
    }
    else
    {
        std::cout << "string to int32 failed, str: " << astr << std::endl;
    }

    bstr = "1234";
    ok = utils::String::stringToUint32(bstr, b);
    if (ok)
    {
        std::cout << "string to uint32: " << b << std::endl;
    }
    else
    {
        std::cout << "string to uint32 failed, str: " << bstr << std::endl;
    }

    cstr = "1234";
    ok = utils::String::stringToInt64(cstr, c);
    if (ok)
    {
        std::cout << "string to int64: " << c << std::endl;
    }
    else
    {
        std::cout << "string to int64 failed, str: " << cstr << std::endl;
    }

    dstr = "1234";
    ok = utils::String::stringToUint64(dstr, d);
    if (ok)
    {
        std::cout << "string to uint64: " << d << std::endl;
    }
    else
    {
        std::cout << "string to uint64 failed, str: " << dstr << std::endl;
    }

    estr = "1.2qq34";
    ok = utils::String::stringToFloat(estr, e);
    if (ok)
    {
        std::cout << "string to float: " << e << std::endl;
    }
    else
    {
        std::cout << "string to float failed, str: " << estr << std::endl;
    }

    fstr = "1.234";
    ok = utils::String::stringToDouble(fstr, f);
    if (ok)
    {
        std::cout << "string to double: " << f << std::endl;
    }
    else
    {
        std::cout << "string to double failed, str: " << fstr << std::endl;
    }


    std::cout << "##################string time_t############################" << std::endl;
    time_t t = time(NULL);
    std::cout << "t: " << t << std::endl;
    std::string strtime = utils::String::time_tToString(t);
    std::cout << "strtime: " << strtime << std::endl;
    std::cout << "t: " << utils::String::stringToTime_t(strtime) << std::endl;

    return 0;
}
