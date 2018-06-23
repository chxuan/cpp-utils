/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogStream.cpp
* @brief 日志流格式化类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-23
*/

#include "LogStream.h"
#include "LogImpl.h"

LogStream::LogStream(const std::string& filePath,
                     const std::string& function,
                     unsigned long line,
                     unsigned int priorityLevel)
    : m_priorityLevel(priorityLevel)
{
    if (m_buffer.use_count() == 0)
    {
        m_buffer = std::make_shared<std::ostringstream>();
    }

    std::string strFilePath = filePath;
    int pos = strFilePath.find_last_of("/");
    (*m_buffer) << strFilePath.substr(pos + 1) << " " << function << "(" << line << ") ";
}

LogStream::~LogStream()
{
    assert(m_buffer.use_count() != 0);
    bool ok = LogImpl::getInstance()->logPrint(m_priorityLevel, m_buffer->str());
    if (!ok)
    {
        std::cout << "Print log failed, log content: " << m_buffer->str() << std::endl;
    }
}
