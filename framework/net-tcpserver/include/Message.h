/* Copyright(C)
* For free
* All right reserved
*
*/
/**
* @file Message.h
* @brief 用于接收tcp消息
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2016-02-03
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <memory>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>

#define TCP_MESSAGE_HEADER unsigned int m_messageType

/**
* @brief 用于tcp服务器接收的消息结构
*/
class Message
{
public:
    TCP_MESSAGE_HEADER;

    std::string m_data;
};

using MessagePtr = std::shared_ptr<Message>;

#endif
