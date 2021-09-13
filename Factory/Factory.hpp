#ifndef _FACTORY_H
#define _FACTORY_H

#include <unordered_map>
#include <functional>
#include <memory>
#include <type_traits>
#include "Message.hpp"

class Factory
{
public:
    Factory() = delete;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    template<typename T>
    static void registerMessage(int key)
    {
        m_messageMap.emplace(key, []{ return new T(); });
    }

    template <typename T, typename... Args>
    static void registerMessage(int key, const Args&... args)
    {
        m_messageMap.emplace(key, [=] { return new T(args...); });
    }

    static Message* get(int key)
    {
        auto iter = m_messageMap.find(key);
        if (iter == m_messageMap.end())
        {
            return nullptr;
        }
        return iter->second();
    }

    static std::unique_ptr<Message> getUnique(int key)
    {
        return std::unique_ptr<Message>(get(key));
    }

    static std::shared_ptr<Message> getShared(int key)
    {
        return std::shared_ptr<Message>(get(key));
    }

    using MessageID = int;
    using MessageCreationFunc = std::function<Message*()>;

private:
    static std::unordered_map<MessageID, MessageCreationFunc> m_messageMap;
};
// warning : this imply header only include once
std::unordered_map<Factory::MessageID, Factory::MessageCreationFunc> Factory::m_messageMap;

#endif
