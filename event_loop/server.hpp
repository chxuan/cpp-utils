#pragma once

#include "event_loop.hpp"
#include <thread>

class server
{
public:
    server()
    {
        std::cout << "server starting..." << std::endl;
    }

    ~server()
    {
        std::cout << "server stoped..." << std::endl;
    }

    void start()
    {
        std::thread t([this](){ task_thread(); });
        t.detach();
    }

private:
    void task_thread()
    {
        while (event_loop::is_active())
        {
            std::cout << "runing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};
