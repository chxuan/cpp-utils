#ifndef _PEOPLEINFOMESSAGE_H
#define _PEOPLEINFOMESSAGE_H

#include "Message.h"

class PeopleInfoMessage
{
public:
    PeopleInfoMessage()
    {
        m_age = 0;
        m_sex = 0;
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void)version;
        ar & m_name;
        ar & m_age;
        ar & m_sex;
    }

    TCP_MESSAGE_HEADER;

    std::string m_name;
    unsigned int m_age;
    unsigned int m_sex;
};

using PeopleInfoMessagePtr = std::shared_ptr<PeopleInfoMessage>;

#endif
