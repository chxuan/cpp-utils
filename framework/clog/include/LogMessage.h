/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogMessage.h
* @brief 日志消息类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-23
*/

#ifndef _LOGMESSAGE_H
#define _LOGMESSAGE_H

#include <string>
#include "LogStream.h"

/**
* @brief 日志消息类
*/
class LogMessage
{
public:
    /**
    * @brief LogMessage 构造函数
    *
    * @param filePath 文件路径
    * @param function 函数名
    * @param line 代码行数
    * @param priorityLevel 日志优先级
    */
    LogMessage(const char* filePath,
               const char* function,
               unsigned long line,
               unsigned int priorityLevel);

    /**
    * @brief log C风格日志函数
    *
    * @param msg 消息字符串
    * @param ... 可变参数
    */
    void log(const char* msg, ...);

    /**
    * @brief log C++风格日志函数
    *
    * @return 日志流对象
    */
    LogStream log() const;

private:
    /**
    * @brief logPrintImpl 日志打印函数
    *
    * @param filePath 文件路径
    * @param function 函数名
    * @param line 代码行数
    * @param priorityLevel 日志优先级
    * @param content 日志输入文本
    */
    void logPrintImpl(const std::string& filePath,
                      const std::string& function,
                      unsigned long line,
                      unsigned int priorityLevel,
                      const std::string& content);

    /**
    * @brief createLogContent 创建一个日志文本
    *
    * @param filePath 文件路径
    * @param function 函数名
    * @param line 代码行数
    * @param content 日志输入文本
    *
    * @return 一个带有日志定为功能的日志文本
    */
    std::string createLogContent(const std::string& filePath,
                                 const std::string& function,
                                 unsigned long line,
                                 const std::string& content);

private:
    std::string m_filePath;             ///< 文件路径
    std::string m_function;             ///< 函数名
    unsigned long m_line = 0;           ///< 代码行数
    unsigned int m_priorityLevel = 0;   ///< 日志优先级
};

#endif
