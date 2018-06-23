/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogImpl.h
* @brief 日志库接口定义
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-12-05
*/

#ifndef _LOGIMPL_H
#define _LOGIMPL_H

#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <string>

/**
* @brief 日志实现类
*/
class LogImpl
{
public:
    LogImpl();
    ~LogImpl();
    LogImpl(const LogImpl& var) = delete;
    LogImpl& operator=(const LogImpl& var) = delete;

    /**
    * @brief getInstance 得到日志实现类指针
    *
    * @return 日志实现类指针
    */
    static LogImpl* getInstance();

    /**
    * @brief logPrint 打印日志
    *
    * @param priorityLevel 日志优先级
    * @param logContent 日志内容
    *
    * @return 成功返回true，否则返回false
    */
    bool logPrint(unsigned int priorityLevel, const std::string& logContent);

private:
    /**
    * @brief init 初始化日志框架
    *
    * @return 成功返回true，否则返回false
    */
    bool init();

    /**
    * @brief deinit 释放资源
    */
    void deinit();

    /**
    * @brief createLogFile 创建日志输出文件
    *
    * @return 日志文件路径
    */
    std::string createLogFile();

    /**
    * @brief initLogCore 初始化日志框架核心
    *
    * @param logFileName 日志文件路径
    *
    * @return 成功返回true，否则返回false
    */
    bool initLogCore(const std::string& logFileName);

private:
    log4cpp::Category* m_root = nullptr;             ///< 日志类别指针
    bool m_isInitSuccess = false;                    ///< 日志框架是否初始化成功
};

#endif
