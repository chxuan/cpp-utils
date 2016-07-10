#include <iostream>
#include "Traits.hpp"

/* template<typename T> struct is_tuple : is_specialization_of<detail::decay_t<T>, std::tuple>{}; */
/* template<typename T> struct is_queue : is_specialization_of<detail::decay_t<T>, std::queue>{}; */
/* template<typename T> struct is_stack : is_specialization_of<detail::decay_t<T>, std::stack>{}; */
/* template<typename T> struct is_set : is_specialization_of<detail::decay_t<T>, std::set> {}; */
/* template<typename T> struct is_multiset : is_specialization_of<detail::decay_t<T>, std::multiset> {}; */
/* template<typename T> struct is_unordered_set : is_specialization_of<detail::decay_t<T>, std::unordered_set> {}; */
/* template<typename T> struct is_priority_queue : is_specialization_of<detail::decay_t<T>, std::priority_queue>{}; */
/* template<typename T> struct is_pair : is_specialization_of<detail::decay_t<T>, std::pair> {}; */

template<typename T>
typename std::enable_if<is_tuple<T>::value>::type testTraits(T&& t)
{
    (void)t;
    std::cout << "is tuple" << std::endl;
}

template<typename T>
typename std::enable_if<is_set<T>::value>::type testTraits(T&& t)
{
    (void)t;
    std::cout << "is set" << std::endl;
}

int main()
{
    testTraits(std::forward_as_tuple(1, "Hello"));
    std::set<int> s {1};
    testTraits(s);
    return 0;
}
