/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogMessage.cpp
* @brief 日志消息类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-01-23
*/

#include "LogMessage.h"
#include "LogImpl.h"
#include "Utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>

LogMessage::LogMessage(const char* filePath,
                       const char* function,
                       unsigned long line,
                       unsigned int priorityLevel)
    : m_filePath(filePath),
    m_function(function),
    m_line(line),
    m_priorityLevel(priorityLevel)
{
    // Do nothing
}

void LogMessage::log(const char* msg, ...)
{
    char buf[4096] = {'\0'};
    va_list args;
    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    logPrintImpl(m_filePath, m_function, m_line, m_priorityLevel, buf);
}

LogStream LogMessage::log() const
{
    return LogStream(m_filePath, m_function, m_line, m_priorityLevel);
}

void LogMessage::logPrintImpl(const std::string& filePath,
                              const std::string& function,
                              unsigned long line,
                              unsigned int priorityLevel,
                              const std::string& content)
{
    std::string logContent = createLogContent(filePath, function, line, content);
    bool ok = LogImpl::getInstance()->logPrint(priorityLevel, logContent);
    if (!ok)
    {
        std::cout << "Print log failed, log content: " << logContent << std::endl;
    }
}

std::string LogMessage::createLogContent(const std::string& filePath,
                                         const std::string& function,
                                         unsigned long line,
                                         const std::string& content)
{
    std::string strLine = utils::String::uint64ToString(line);
    std::string strFilePath = filePath;
    int pos = strFilePath.find_last_of("/");
    std::string logContent = strFilePath.substr(pos + 1) + " " + function + "(" + strLine + ") " + content;

    return logContent;
}
