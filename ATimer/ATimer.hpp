#ifndef _ATIMER_H
#define _ATIMER_H

#include <vector>
#include <thread>
#include <functional>
#include <boost/timer.hpp>
#include <boost/asio.hpp>

class ATimer
{
public:
    ATimer() : m_timer(m_ios, boost::posix_time::milliseconds(0)) {}

    void start(unsigned int mill)
    {
        if (m_ios.stopped())
        {
            return;
        }

        m_milliseconds = mill;
        m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(m_milliseconds));
        m_func = [this]
        {
            m_timer.async_wait([this](const boost::system::error_code&)
            {
                for (auto& func : m_funcVec)
                {
                    func();
                }
                m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(m_milliseconds));
                m_func();
            });
        };

        m_func();
        m_thread = std::thread([this]{ m_ios.run(); });
    }

    void stop()
    {
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

private:
    boost::asio::io_service m_ios;
    boost::asio::deadline_timer m_timer;
    std::function<void()> m_func;
    std::vector<std::function<void()>> m_funcVec;
    std::thread m_thread;
    unsigned int m_milliseconds = 0;
};

#endif
