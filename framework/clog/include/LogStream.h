/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogStream.h
* @brief 日志流格式化类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-23
*/

#ifndef _LOGSTREAM_H
#define _LOGSTREAM_H

#include <assert.h>
#include <iostream>
#include <sstream>
#include <memory>

/**
* @brief 日志流对象
*/
class LogStream
{
public:
    /**
    * @brief LogStream 构造函数
    *
    * @param filePath 文件路径
    * @param function 函数名
    * @param line 代码行数
    * @param priorityLevel 日志优先级
    */
    LogStream(const std::string& filePath,
              const std::string& function,
              unsigned long line,
              unsigned int priorityLevel);
    ~LogStream();

    /**
    * @brief << 从载输入操作符
    *
    * @tparam T 模板类型
    * @param t 模板类对象
    *
    * @return 日志流对象
    */
    template<typename T>
    LogStream& operator << (const T& t)
    {
        assert(m_buffer.use_count() != 0);
        (*m_buffer) << t;
        return *this;
    }

private:
    using OStringStreamPtr = std::shared_ptr<std::ostringstream>;
    OStringStreamPtr m_buffer;              ///< 字符串输入流对象

    unsigned int m_priorityLevel = 0;      ///< 日志优先级
};

#endif
