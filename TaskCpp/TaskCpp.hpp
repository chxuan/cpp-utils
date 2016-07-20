#ifndef _TASKCPP_H
#define _TASKCPP_H

namespace taskcpp
{

template<typename T>
class Task;

template<typename R, typename... Args>
class Task<R(Args...)>
{
public:

};

};

#endif
