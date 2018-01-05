#pragma once

#include <random>
#include <chrono>
using namespace std;

class random_generator
{
public:
    random_generator() 
    { 
        engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    // 生成int类型随机数，返回范围[min, max]
    int randint(int min,int max)
    {
        uniform_int_distribution<int> u(min,max);
        return u(engine);
    }

private:
    std::default_random_engine engine;
};
