#include "shared_mutex.h"
#include <iostream>
#include <thread>
 
class ThreadSafeCounter 
{
public:
    ThreadSafeCounter() = default;

    unsigned int get() 
    {
        lock_shared lock(mutex_, true);
        return value_;
    }

    void increment() 
    {
        lock_shared lock(mutex_);
        value_++;
    }

    void reset() 
    {
        lock_shared lock(mutex_);
        value_ = 0;
    }

private:
    shared_mutex mutex_;
    unsigned int value_ = 0;
};

int main() 
{
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() 
    {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';
        }
    };

    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);

    thread1.join();
    thread2.join();

    return 0;
}
