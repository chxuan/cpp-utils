/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogImpl.cpp
* @brief 日志库接口实现
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-12-05
*/

#include "LogImpl.h"
#include "Utils.h"
#include <stdio.h>
#include <iostream>

#define DEFAULT_LOG_PRIORITY        (log4cpp::Priority::DEBUG)      // 日志文件默认优先级
#define MAX_LOGFILE_SIZE            (3*1024*1024)                   // 日志文件默认大小
#define MAX_BACKUP_LOGFILE_COUNT    (30)                            // 默认保存历史日志数量

LogImpl::LogImpl()
{
    m_isInitSuccess = init();
    if (!m_isInitSuccess)
    {
        std::cout << "Init log failed" << std::endl;
    }
}

LogImpl::~LogImpl()
{
    deinit();
}

LogImpl* LogImpl::getInstance()
{
    static LogImpl logImpl;
    return &logImpl;
}

bool LogImpl::logPrint(unsigned int priorityLevel, const std::string& logContent)
{
    if (!m_isInitSuccess)
    {
        return false;
    }

    m_root->log(priorityLevel, logContent);

    return true;
}

bool LogImpl::init()
{
    std::string logFileName = createLogFile();
    if (logFileName.empty())
    {
        std::cout << "Create log file failed" << std::endl;
        return false;
    }

    bool ok = initLogCore(logFileName);
    if (!ok)
    {
        std::cout << "Init log core failed, log file name: " << logFileName << std::endl;
        return false;
    }

    return true;
}

void LogImpl::deinit()
{
    log4cpp::Category::shutdown();
}

std::string LogImpl::createLogFile()
{
    // 获取当前可执行文件所在路径
    std::string exePath = utils::FileSystem::currentExePath();
    if (exePath.empty())
    {
        std::cout << "Get current exe path failed" << std::endl;
        return "";
    }

    // 创建日志路径
    std::string logPath = exePath + "/logs";
    bool ok = utils::FileSystem::mkdir(logPath);
    if (!ok)
    {
        std::cout << "Create log path failed, log path: " << logPath << std::endl;
        return "";
    }

    // 获取当前可执行文件名
    std::string exeName = utils::FileSystem::currentExeName();
    if (exeName.empty())
    {
        std::cout << "Get current exe name failed" << std::endl;
        return "";
    }

    // 日志文件名
    std::string logFileName = logPath + "/" + exeName + ".log";
    return logFileName;
}

bool LogImpl::initLogCore(const std::string& logFileName)
{
    log4cpp::PatternLayout* fileLayout = new log4cpp::PatternLayout();
    fileLayout->setConversionPattern("%d: [%-5p] %c%x: %m%n");

    log4cpp::PatternLayout* consoleLayout = new log4cpp::PatternLayout();
    consoleLayout->setConversionPattern("%d: [%-5p] %c%x: %m%n");

    log4cpp::RollingFileAppender* rollfileAppender =
                        new log4cpp::RollingFileAppender("rollfileAppender", logFileName, MAX_LOGFILE_SIZE, 1);
    rollfileAppender->setMaxBackupIndex(MAX_BACKUP_LOGFILE_COUNT);
    rollfileAppender->setLayout(fileLayout);

    log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
    osAppender->setLayout(consoleLayout);

    m_root = &(log4cpp::Category::getRoot().getInstance(""));

    // 一个Category可以附加多个Appender
    m_root->setAdditivity(true);
    m_root->addAppender(rollfileAppender);
    m_root->addAppender(osAppender);
    m_root->setPriority(DEFAULT_LOG_PRIORITY);

    return true;
}
