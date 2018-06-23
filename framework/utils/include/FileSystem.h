/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file FileSystem.h
* @brief 文件系统工具实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-28
*/

#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include <time.h>
#include <string>
#include <sstream>

namespace utils
{
/**
 * @brief 文件、路径操作
 */
class FileSystem
{
public:
    /**
     * @brief currentWorkPath 获取当前程序的工作目录
     *
     * @return 工作目录
     *
     * @note 失败将返回空字符串
     */
    static std::string currentWorkPath();

    /**
     * @brief setCurrentWorkPath 设置当前程序的工作目录
     *
     * @param path 工作目录
     *
     * @return 成功返回true，否则返回false
     */
    static bool setCurrentWorkPath(const std::string& path);

    /**
     * @brief currentExePath 获得当前可执行文件所在目录
     *
     * @return 可执行文件所在目录
     *
     * @note 失败将返回空字符串
     */
    static std::string currentExePath();

    /**
     * @brief currentExeName 获得当前可执行文件名
     *
     * @return 可执行文件名
     *
     * @note 失败将返回空字符串
     */
    static std::string currentExeName();

    /**
     * @brief isExists 判断一个文件或目录是否存在
     *
     * @param path 文件或目录路径
     *
     * @return 存在返回true，否则返回false
     */
    static bool isExists(const std::string& path);

    /**
     * @brief mkdir 创建多级目录
     *
     * @param path 路径
     *
     * @return 成功返回true，否则返回false
     */
    static bool mkdir(const std::string& path);

    /**
     * @brief remove 删除文件或目录
     *
     * @param path 路径
     *
     * @note 目录里面有内容，返回false，并且不能够递归删除目录
     *
     * @return 成功返回true，否则返回false
     */
    static bool remove(const std::string& path);
};
}

#endif
