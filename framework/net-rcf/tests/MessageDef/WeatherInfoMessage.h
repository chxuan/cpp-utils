/*************************************************************************
	> File Name: WeatherInfoMessage.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月17日 星期日 09时28分11秒
 ************************************************************************/

#ifndef _WEATHERINFOMESSAGE_H
#define _WEATHERINFOMESSAGE_H

#include <string>
#include <RCF/RCF.hpp>

class WeatherInfoMessage
{
public:
    void serialize(SF::Archive& ar)
    {
        ar & m_weatherDescription;
    }

    std::string     m_weatherDescription;
};

#endif
