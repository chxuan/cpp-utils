/**
 * @file random_generator.h
 * @brief 随机数生成器
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2018-01-05
 */
#pragma once

#include <random>
#include <chrono>

class random_generator
{
public:
    random_generator() 
    { 
        engine_.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    // 生成int类型随机数，返回范围[min, max]
    int randint(int min, int max)
    {
        std::uniform_int_distribution<int> u(min, max);
        return u(engine_);
    }

    // 生成double类型随机数，返回范围[min, max]
    double randreal(double min, double max)
    {
        std::uniform_real_distribution<double> u(min, max);
        return u(engine_);
    }

private:
    std::default_random_engine engine_;
};
