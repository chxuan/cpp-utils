/**
 * @file singletion.h
 * @brief 单例模板
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-12-01
 */
#pragma once

#include <mutex>
#include <memory>

template<typename T>
class singletion
{
public:
	static std::shared_ptr<T> get_instance() 
    {
        if (inst_ == nullptr) 
        {
            static std::mutex mt;
            std::lock_guard<std::mutex> lock(mt);
            if (inst_ == nullptr) 
            { 
                inst_ = std::make_shared<T>();
            } 
        }

        return inst_; 
    }

    singletion() = delete;
    singletion(const singletion&) = delete;
    singletion& operator=(const singletion&) = delete;

private:
    static std::shared_ptr<T> inst_;
};

template<typename T>
std::shared_ptr<T> singletion<T>::inst_ = nullptr;
