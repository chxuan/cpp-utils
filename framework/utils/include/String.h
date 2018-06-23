/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file String.h
* @brief 字符串转换工具实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-28
*/

#ifndef _STRING_H
#define _STRING_H

#include <time.h>
#include <string>
#include <sstream>

namespace utils
{
/**
 * @brief 字符串与其他类型的相互转换
 */
class String
{
public:
    /**
     * @brief int32ToString int类型转换成string类型
     *
     * @param n int类型
     *
     * @return string类型
     */
    static std::string int32ToString(int n);

    /**
     * @brief uint32ToString unsigned int类型转换成string类型
     *
     * @param n unsigned int类型
     *
     * @return string类型
     */
    static std::string uint32ToString(unsigned int n);

    /**
     * @brief int64ToString long long类型转换成string类型
     *
     * @param n long long类型
     *
     * @return string类型
     */
    static std::string int64ToString(long long n);

    /**
     * @brief uint64ToString unsigned long long类型转换成string类型
     *
     * @param n unsigned long long类型
     *
     * @return string类型
     */
    static std::string uint64ToString(unsigned long long n);

    /**
     * @brief floatToString float类型转换成string类型
     *
     * @param n float类型
     *
     * @return string类型
     */
    static std::string floatToString(float n);

    /**
     * @brief doubleToString double类型转换成string类型
     *
     * @param n double类型
     *
     * @return string类型
     */
    static std::string doubleToString(double n);

    /**
     * @brief time_tToString time_t类型转换成string类型
     *
     * @param n time_t类型
     *
     * @note 转换格式，默认为"%d-%d-%d %d:%d:%d"
     *
     * @return string类型
     */
    static std::string time_tToString(time_t n);

    /**
     * @brief stringToInt32 string类型转换成int类型
     *
     * @param str string类型
     * @param n int类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToInt32(const std::string& str, int& n);

    /**
     * @brief stringToUint32 string类型转换成unsigned int类型
     *
     * @param str string类型
     * @param n unsigned int类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToUint32(const std::string& str, unsigned int& n);

    /**
     * @brief stringToInt64 string类型转换成long long类型
     *
     * @param str string类型
     * @param n long long类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToInt64(const std::string& str, long long& n);

    /**
     * @brief stringToUint64 string类型转换成unsigned long long类型
     *
     * @param str string类型
     * @param n unsigned long long类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToUint64(const std::string& str, unsigned long long& n);

    /**
     * @brief stringToFloat string类型转换成float类型
     *
     * @param str string类型
     * @param n float类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToFloat(const std::string& str, float& n);

    /**
     * @brief stringToDouble string类型转换成double类型
     *
     * @param str string类型
     * @param n double类型
     *
     * @return 成功返回true，否则返回false
     */
    static bool stringToDouble(const std::string& str, double& n);

    /**
     * @brief stringToTime_t string类型转换成time_t类型
     *
     * @param time 字符串时间
     *
     * @note 时间格式:2015-11-30 20:21:34
     *
     * @return time_t表示的时间
     */
    static time_t stringToTime_t(const std::string& time);

private:
    template<typename T>
    static typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type tToString(T t)
    {
        return std::to_string(t);
    }

    template<typename T>
    static typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type tToString(T t)
    {
        return t;
    }

    template<typename T>
    static bool stringToT(const std::string& str, T& t)
    {
        std::stringstream ss;
        ss << str;
        ss >> t;
        return !ss.good();
    }
};
}

#endif
