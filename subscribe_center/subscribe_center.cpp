#include "subscribe_center.h"

void subscribe_center::add_message(const std::string& message_name, const std::string& session_id)
{
    lock_shared lock(mutex_);
    auto range = message_to_session_.equal_range(message_name);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second == session_id)
        {
            return;
        }
    }

    message_to_session_.emplace(message_name, session_id);
}

std::vector<std::string> subscribe_center::get_session_id(const std::string& message_name)
{
    lock_shared lock(mutex_, true);
    std::vector<std::string> session_ids;
    auto range = message_to_session_.equal_range(message_name);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        session_ids.emplace_back(iter->second);
    }

    return session_ids;
}

void subscribe_center::remove_message(const std::string& session_id)
{
    lock_shared lock(mutex_);
    auto begin = message_to_session_.begin();
    while (begin != message_to_session_.end())
    {
        if (begin->second == session_id)
        {
            begin = message_to_session_.erase(begin);
        }
        else
        {
            ++begin;
        }
    }
}

void subscribe_center::clear()
{
    lock_shared lock(mutex_);
    message_to_session_.clear();
}
