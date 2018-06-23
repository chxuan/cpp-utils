/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月20日 星期三 17时08分08秒
 ************************************************************************/

#include <iostream>
#include <string>
#include "PubSubProtocolDefine.h"
#include "RCFSubscriberWrapper.hpp"

class RCFMessageHandler
{
public:
    void pushWeather(const WeatherInfoMessage& weatherInfo)
    {
        std::cout << weatherInfo.m_weatherDescription << std::endl;
    }

    void pushNews(const std::string& newsInfo)
    {
        std::cout << newsInfo << std::endl;
    }
};

int main()
{
    RCFSubscriberWrapper<I_PubSubMessageHandler> server;
    RCFMessageHandler rcfMessageHandler;

    bool ok = server.start();
    if (ok)
    {
        std::cout << "Subscriber server start..." << std::endl;
    }
    else
    {
        std::cout << "Subscriber server start failed" << std::endl;
        return -1;
    }

    SubscriptionParam param;
    param.m_ip = "127.0.0.1";
    param.m_port = 50003;
    param.m_topicName = "weather";
    ok = server.createSubscription(rcfMessageHandler, param);
    if (ok)
    {
        std::cout << "Subscription topic success, topic name: " << param.m_topicName << std::endl;
    }
    else
    {
        std::cout << "Subscription topic failed, topic name: " << param.m_topicName << std::endl;
        return -1;
    }

    SubscriptionParam param2;
    param2.m_ip = "127.0.0.1";
    param2.m_port = 50003;
    param2.m_topicName = "news";
    ok = server.createSubscription(rcfMessageHandler, param2);
    if (ok)
    {
        std::cout << "Subscription topic success, topic name: " << param2.m_topicName << std::endl;
    }
    else
    {
        std::cout << "Subscription topic failed, topic name: " << param2.m_topicName << std::endl;
        return -1;
    }

    std::cin.get();

    std::cout << "Subscriber server stoped..." << std::endl;

    return 0;
}
