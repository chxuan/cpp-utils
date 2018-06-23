/*************************************************************************
	> File Name: PeopleInfoMessage.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月10日 星期日 19时58分32秒
 ************************************************************************/

#ifndef _PEOPLEINFOMESSAGE_H
#define _PEOPLEINFOMESSAGE_H

#include <string>
#include <RCF/RCF.hpp>

class PeopleInfoMessage
{
public:
    void serialize(SF::Archive& ar)
    {
        ar & m_name & m_age;
    }

    std::string     m_name;
    unsigned int    m_age;
};

#endif
