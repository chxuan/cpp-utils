/**
 * @file singletion.h
 * @brief 单例模板
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-12-01
 */
#pragma once

template<typename T>
class singletion
{
public:
    static T& get_instance() 
    {
        // C++11保证静态变量的线程安全
        static T t;
        return t; 
    }

    singletion() = delete;
    singletion(const singletion&) = delete;
    singletion& operator=(const singletion&) = delete;
};
