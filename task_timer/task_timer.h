#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <boost/timer.hpp>
#include <boost/asio.hpp>

template<typename Duration = boost::posix_time::milliseconds>
class task_timer
{
public:
    task_timer() : work_(ios_), timer_(ios_) {}
    ~task_timer()
    {
        destroy();
    }

    void start(std::size_t duration)
    {
        if (ios_.stopped())
        {
            return;
        }

        duration_ = duration;
        thread_ = std::thread([this]{ ios_.run(); });
        start();
    }

    void start()
    {
        timer_.expires_from_now(Duration(duration_));
        timer_.async_wait([this](const boost::system::error_code& ec)
        {
            if (ec)
            {
                return;
            }

            for (auto& func : func_vec_)
            {
                func();
            }

            if (!is_single_shot_)
            {
                start();
            }
        });
    }

    void stop()
    {
        timer_.cancel();
    }

    void destroy()
    {
        stop();
        ios_.stop();
        if (thread_.joinable())
        {
            thread_.join();
        }
    }

    void bind(const std::function<void()>& func)
    {
        func_vec_.emplace_back(func);
    }

    void set_single_shot(bool is_single_shot)
    {
        is_single_shot_ = is_single_shot; 
    }

private:
    boost::asio::io_service ios_;
    boost::asio::io_service::work work_;
    boost::asio::deadline_timer timer_;
    std::vector<std::function<void()>> func_vec_;
    std::thread thread_;
    std::size_t duration_ = 0;
    std::atomic<bool> is_single_shot_ { false };
};
