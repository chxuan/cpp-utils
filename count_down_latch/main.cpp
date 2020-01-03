#include <iostream>
#include <thread>
#include "count_down_latch.hpp"

count_down_latch latch(3);

void worker_thread(const std::string& name)
{
    std::cout << name << "正在干活..." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    latch.count_down();

    std::cout << name << "干完活了!" << std::endl;
}

void boss_thread()
{
    std::cout << "老板正在等所有的工人干完活..." << std::endl;

    latch.await();

    std::cout << "工人活都干完了，老板开始检查了!" << std::endl;
}

int main()
{
    std::thread b(boss_thread);

    std::thread w1([]{ worker_thread("张三"); });
    std::thread w2([]{ worker_thread("李四"); });
    std::thread w3([]{ worker_thread("王五"); });

    b.join();
    w1.join();
    w2.join();
    w3.join();

    return 0;
}
