/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file CThreadManage.h
* @brief 线程池管理类
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-17
*/

#ifndef _CTHREADMANAGE_H
#define _CTHREADMANAGE_H

#include <memory>

class CThreadPool;
class CJob;

/**
* @brief 线程池管理类，管理CThreadPool
*/
class CThreadManage
{
public:
    using CThreadPoolPtr = std::shared_ptr<CThreadPool>;
    using CJobPtr = std::shared_ptr<CJob>;

    CThreadManage();
    ~CThreadManage();

public:
    /**
    * @brief initThreadNum 初始化线程数量
    *
    * @param initNumOfThread 线程数量
    */
    void initThreadNum(unsigned int initNumOfThread);

    /**
    * @brief run 执行具体的job
    *
    * @param job 具体的任务
    */
    void run(CJobPtr job);

    /**
    * @brief terminateAll 终止全部的线程
    */
    void terminateAll();

private:
    CThreadPoolPtr m_threadPool;
};

using CThreadManagePtr = std::shared_ptr<CThreadManage>;

#endif
