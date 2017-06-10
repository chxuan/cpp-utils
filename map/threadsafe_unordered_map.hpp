#pragma once

#include <unordered_map>
#include <mutex>

template<typename Key, typename Value>
class threadsafe_unordered_map
{
public:
    void emplace(const Key& key, const Value& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.emplace(key, value);
    }

    bool replace(const Key& key, const Value& value, Value* out_value = nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        bool is_update = false;
        auto iter = map_.find(key);
        if (iter == map_.end())
        {
            map_.emplace(key, value);
        }
        else
        {
            is_update = true;
            if (out_value != nullptr)
            {
                *out_value = iter->second;
            }
            iter->second = value;
        }

        return is_update;
    }

    void erase(const Key& key)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.erase(key);
    }

    bool erase(const Key& key, const Value& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto iter = map_.find(key);
        if (iter != map_.end())
        {
            if (iter->second == value)
            {
                map_.erase(iter);
                return true;
            }
        }
        return false;
    }

    void for_each(const std::function<void(const Key&, const Value&)>& func)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& iter : map_)
        {
            func(iter.first, iter.second);
        }
    }

    void for_each_key(const std::function<void(const Key&)>& func)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& iter : map_)
        {
            func(iter.first);
        }
    }

    void for_each_value(const std::function<void(const Value&)>& func)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& iter : map_)
        {
            func(iter.second);
        }
    }

    void for_each_erase(const std::function<bool(const Key&, const Value&)>& func)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto begin = map_.begin();
        while (begin != map_.end())
        {
            if (func(begin->first, begin->second))
            {
                begin = map_.erase(begin);
            }
            else
            {
                ++begin;
            }
        }
    }

    bool find(const Key& key, Value& out_value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto iter = map_.find(key);
        if (iter != map_.end())
        {
            out_value = iter->second;
            return true;
        }
        return false;
    }

    bool exists(const Key& key)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto iter = map_.find(key);
        if (iter != map_.end())
        {
            return true;
        }
        return false;
    }

    std::unordered_map<Key, Value> clone() 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_;
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.clear();
    }

    std::size_t size()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_.size();
    }
    
private:
    std::unordered_map<Key, Value> map_;
    std::mutex mutex_;
};
