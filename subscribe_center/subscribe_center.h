/**
 * @file subscribe_center.h
 * @brief 消息订阅中心
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2018-01-01
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "lock_shared.h"

class subscribe_center
{
public:
    void add_message(const std::string& message_name, const std::string& session_id);
    std::vector<std::string> get_session_id(const std::string& message_name);
    void remove_message(const std::string& session_id);
    void clear();

private:
    std::unordered_multimap<std::string, std::string> message_to_session_;
    shared_mutex mutex_;
};
