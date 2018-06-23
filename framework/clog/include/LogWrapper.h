/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file LogWrapper.h
* @brief 日志库包装接口定义
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-12-05
*/

#ifndef _LOGWRAPPER_H
#define _LOGWRAPPER_H

#include "LogMessage.h"

/// 日志优先级，值越低优先级越高
/// LogWrapper的优先级的值和log4cpp的优先级的值一样，方便映射
enum LogWrapperPriorityLevel
{
    LogWrapperFatalLevel = 0,
    LogWrapperAlertLevel = 100,
    LogWrapperCritLevel = 200,
    LogWrapperErrorLevel = 300,
    LogWrapperWarnLevel = 400,
    LogWrapperNoticeLevel = 500,
    LogWrapperInfoLevel = 600,
    LogWrapperDebugLevel = 700
};

#define LOCATION_INFO          __FILE__, __FUNCTION__, __LINE__

#define logFatal       LogMessage(LOCATION_INFO, LogWrapperFatalLevel).log
#define logAlert       LogMessage(LOCATION_INFO, LogWrapperAlertLevel).log
#define logCrit        LogMessage(LOCATION_INFO, LogWrapperCritLevel).log
#define logError       LogMessage(LOCATION_INFO, LogWrapperErrorLevel).log
#define logWarn        LogMessage(LOCATION_INFO, LogWrapperWarnLevel).log
#define logNotice      LogMessage(LOCATION_INFO, LogWrapperNoticeLevel).log
#define logInfo        LogMessage(LOCATION_INFO, LogWrapperInfoLevel).log
#define logDebug       LogMessage(LOCATION_INFO, LogWrapperDebugLevel).log

#endif
