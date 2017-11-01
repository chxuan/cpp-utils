#pragma once

#include "event_loop.hpp"
#include <thread>
#include <memory>

class server
{
public:
    server()
    {
        std::cout << "server starting..." << std::endl;
    }

    ~server()
    {
        thread_->join();
        std::cout << "server stoped..." << std::endl;
    }

    void start()
    {
         thread_ = std::make_shared<std::thread>(std::bind(&server::task_thread, this));
    }

private:
    void task_thread()
    {
        while (event_loop::is_active())
        {
            std::cout << "runing..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        std::cout << "thread end..." << std::endl;
    }

private:
    std::shared_ptr<std::thread> thread_;
};
