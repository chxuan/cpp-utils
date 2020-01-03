#include <iostream>
#include <thread>
#include "cyclic_barrier.hpp"

cyclic_barrier barrier(3);

void worker_thread(const std::string& name)
{
    std::cout << name << "正在打桩，毕竟不轻松..." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << name << "不容易，终于把桩打完了..." << std::endl;

    barrier.await();

    std::cout << name << ":其他逗b把桩都打完了，又得忙活了..." << std::endl;
}

int main()
{
    std::thread w1([]{ worker_thread("张三"); });
    std::thread w2([]{ worker_thread("李四"); });
    std::thread w3([]{ worker_thread("王五"); });

    w1.join();
    w2.join();
    w3.join();

    return 0;
}
