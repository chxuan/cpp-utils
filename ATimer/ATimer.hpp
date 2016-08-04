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
    ATimer() : m_timer(m_ios, Duration(0)), m_isSingleShot(false) {}
    ~ATimer()
    {
        stop();
    }

    void start(unsigned int duration)
    {
        if (m_ios.stopped())
        {
            return;
        }

        m_isActive = true;
        m_duration = duration;
        m_timer.expires_at(m_timer.expires_at() + Duration(m_duration));
        m_func = [this]
        {
            m_timer.async_wait([this](const boost::system::error_code&)
            {
                for (auto& func : m_funcVec)
                {
                    func();
                }

                if (!m_isSingleShot)
                {
                    m_timer.expires_at(m_timer.expires_at() + Duration(m_duration));
                    m_func();
                }
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
        m_isActive = false;
    }

    void bind(const std::function<void()>& func)
    {
        m_funcVec.emplace_back(func);
    }

    void setSingleShot(bool isSingleShot)
    {
        m_isSingleShot = isSingleShot; 
    }

    bool isSingleShot() const
    {
        return m_isSingleShot;
    }

    bool isActive() const
    {
        return m_isActive;
    }

private:
    boost::asio::io_service m_ios;
    boost::asio::deadline_timer m_timer;
    std::function<void()> m_func = nullptr;
    std::vector<std::function<void()>> m_funcVec;
    std::thread m_thread;
    unsigned int m_duration = 0;
    std::atomic<bool> m_isSingleShot;
    bool m_isActive = false;
};

#endif
