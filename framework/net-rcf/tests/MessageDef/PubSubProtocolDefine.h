#ifndef _PUBSUBPROTOCOLDEFINE_H
#define _PUBSUBPROTOCOLDEFINE_H

#include <RCF/RCF.hpp>
#include <string>
#include "WeatherInfoMessage.h"

RCF_BEGIN(I_PubSubMessageHandler, "I_PubSubMessageHandler")
    RCF_METHOD_V1(void, pushWeather, const WeatherInfoMessage&)
    RCF_METHOD_V1(void, pushNews, const std::string&)
RCF_END(I_PubSubMessageHandler)

#endif
