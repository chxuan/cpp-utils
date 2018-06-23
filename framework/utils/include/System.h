/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file System.h
* @brief 系统相关工具实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-28
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <time.h>
#include <string>
#include <sstream>

namespace utils
{
/**
 * @brief 系统相关操作
 */
class System
{
public:
    /**
     * @brief uuid 获取uuid
     *
     * @return uuid字符串
     */
    static std::string uuid();

    /**
     * @brief md5 对字符串进行md5加密
     *
     * @param str 待加密的字符串
     *
     * @return 加密后的字符串
     *
     * @note 若加密失败，则返回空字符串
     */
    static std::string md5(const std::string& str);

    /**
     * @brief sha1 对字符串进行sha1加密
     *
     * @param str 待加密的字符串
     *
     * @return 加密后的字符串
     *
     * @note 若加密失败，则返回空字符串
     */
    static std::string sha1(const std::string& str);

    /**
     * @brief totalMemery 获取系统总内存大小
     *
     * @return 成功返回总内存大小，失败返回0
     */
    static unsigned long totalMemery();

    /**
     * @brief freeMemery 获取系统可用内存大小
     *
     * @return 成功返回可用内存大小，失败返回0
     */
    static unsigned long freeMemery();
};
}

#endif
