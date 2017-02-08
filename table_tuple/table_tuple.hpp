#pragma once
#include <string>
#include <list>
#include <unordered_map>
#include <mutex>

template<typename... T>
class table_tuple
{
public:
    table_tuple() = default;

    template<typename... Index>
    table_tuple(Index&&... index)
    {
        static_assert(sizeof...(Index) == sizeof...(T), "Error: parameter number is wrong");
        create_index(std::forward<Index>(index)...);
    }

private:
    void create_index() {}
    template<typename... Index>
    void create_index(const std::string& first, Index&&... rest)
    {
        index_map_.emplace(first, index_map_.size());
        create_index(std::forward<Index>(rest)...);
    }

private:
    std::unordered_map<std::string, std::size_t> index_map_;
    std::mutex mutex_; 
};
