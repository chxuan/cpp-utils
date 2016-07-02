#ifndef _OBJECTPOOL_H
#define _OBJECTPOOL_H

#include <vector>
#include <memory>
#include <functional>

template<typename T>
class ObjectPool
{
public:
    using DeleterType = std::function<void(T*)>;

    void add(std::unique_ptr<T> t)
    {
        m_pool.emplace_back(std::move(t));
    }

    std::unique_ptr<T, DeleterType> get()
    {
        if (m_pool.empty())
        {
            throw std::logic_error("No more object");
        }

        std::unique_ptr<T, DeleterType> ptr(m_pool.back().release(), [this](T* t)
        {
            m_pool.emplace_back(std::unique_ptr<T>(t));
        });

        m_pool.pop_back();
        return std::move(ptr);
    }

    std::shared_ptr<T> getShared()
    {
        if (m_pool.empty())
        {
            throw std::logic_error("No more object");
        }
        
        auto pin = std::unique_ptr<T>(std::move(m_pool.back()));
        m_pool.pop_back();

        return std::shared_ptr<T>(pin.release(), [this](T* t)
        {
            m_pool.emplace_back(std::unique_ptr<T>(t));                         
        });
    }

    bool empty() const
    {
        return m_pool.empty();
    }

    std::size_t size() const
    {
        return m_pool.size();
    }

private:
    std::vector<std::unique_ptr<T>> m_pool;
};

#endif
