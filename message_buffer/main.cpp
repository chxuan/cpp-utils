#include <iostream>
#include <thread>
#include <atomic>
#include "message_buffer.hpp"

message_buffer<int> buffer(500);
std::atomic<bool> is_stop{ false };

void test1()
{
    for (int i = 1; i < 10000; ++i)
    {
        buffer.put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void test2()
{
    while (!is_stop)
    {
        std::list<int> result = buffer.get();
        std::cout << "size: " << result.size() << ", " << result.back() << std::endl;
    }
}

int main()
{
    std::thread t1(test1);
    std::thread t2(test2);
    t1.join();
    is_stop = true;
    buffer.notify_one();
    t2.join();
    return 0;
}
