#pragma once
#include <iostream>
#include <string>
#include <list>
#include <tuple>
#include <unordered_map>
#include <mutex>

template<typename T>
struct element
{
    element(const std::string& in_field_name, const T& in_field_value)
        : field_name(in_field_name), field_value(in_field_value) {}
    std::string field_name;
    T field_value;
};

template<typename... T>
class table_tuple
{
public:
    table_tuple() = default;

    template<typename... Args>
    table_tuple(Args&&... args)
    {
        static_assert(sizeof...(Args) == sizeof...(T), "Error: parameter number is wrong");
        create_table_structure(std::forward<Args>(args)...);
    }

    void insert(T&&... args)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        tuple_list_.emplace_back(std::forward_as_tuple(args...));
    }

    void print()
    {
        for (auto& iter : tuple_list_)
        {
            std::cout << std::get<0>(iter) << ", " << std::get<1>(iter)
                << ", " << std::get<2>(iter) << std::endl;
        }
    }

private:
    void create_table_structure() {}
    template<typename... Args>
    void create_table_structure(const std::string& first, Args&&... rest)
    {
        std::size_t size = table_structure_map_.size();
        std::cout << "first: " << first << ", " << size << std::endl;
        table_structure_map_.emplace(first, size);
        create_table_structure(std::forward<Args>(rest)...);
    }

private:
    std::unordered_map<std::string, std::size_t> table_structure_map_;
    std::list<std::tuple<T...>> tuple_list_;
    std::mutex mutex_; 
};
