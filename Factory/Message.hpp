#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <iostream>

struct Message
{
    virtual ~Message() {}
    virtual void func() = 0;
};

#endif
