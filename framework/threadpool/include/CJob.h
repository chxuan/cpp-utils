/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CJob.h
* @brief 任务父类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-20
*/

#ifndef _CJOB_H
#define _CJOB_H

#include <string>
#include <memory>

/**
* @brief 任务类
*/
class CJob
{
public:
    virtual ~CJob() = default;

    /**
    * @brief run 执行任务
    */
    virtual void run() = 0;

public:
    int jobNo() const { return m_jobNo; }
    void setJobNo(int jobNo) { m_jobNo = jobNo; }

    std::string jobName() const { return m_jobName; }
    void setJobName(const std::string& jobName) { m_jobName = jobName; }

private:
    int m_jobNo = 0;
    std::string m_jobName;
};

using CJobPtr = std::shared_ptr<CJob>;

#endif
