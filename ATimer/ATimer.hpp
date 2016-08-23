#ifndef _ATIMER_H
#define _ATIMER_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <boost/timer.hpp>
#include <boost/asio.hpp>

template<typename Duration = boost::posix_time::milliseconds>
class ATimer
{
public:
    ATimer() : m_work(m_ios), m_timer(m_ios), m_isSingleShot(false) {}
    ~ATimer()
    {
        destroy();
    }

    void start(unsigned int duration)
    {
        if (m_ios.stopped())
        {
            return;
        }

        m_duration = duration;
        m_thread = std::thread([this]{ m_ios.run(); });
        start();
    }

    void start()
    {
        m_timer.expires_from_now(Duration(m_duration));
        m_timer.async_wait([this](const boost::system::error_code& ec)
        {
            if (ec)
            {
                return;
            }

            for (auto& func : m_funcVec)
            {
                func();
            }

            if (!m_isSingleShot)
            {
                start();
            }
        });
    }

    void stop()
    {
        m_timer.cancel();
    }

    void destroy()
    {
        stop();
        m_ios.stop();
        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }

    void bind(const std::function<void()>& func)
    {
        m_funcVec.emplace_back(func);
    }

    void setSingleShot(bool isSingleShot)
    {
        m_isSingleShot = isSingleShot; 
    }

private:
    boost::asio::io_service m_ios;
    boost::asio::io_service::work m_work;
    boost::asio::deadline_timer m_timer;
    std::function<void()> m_func = nullptr;
    std::vector<std::function<void()>> m_funcVec;
    std::thread m_thread;
    unsigned int m_duration = 0;
    std::atomic<bool> m_isSingleShot;
};

#endif
