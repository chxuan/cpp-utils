/* Copyright(C)
* For free
* All right reserved
* 
*/
/**
* @file Message.h
* @brief thrift消息传输定义
* @author highway-9, 787280310@qq.com
* @version 1.1.0
* @date 2015-11-25
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <sstream>
#include <string>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>

/**
* @brief thrift消息定义
*/
class Message
{
public:
    /**
    * @brief serializeSelf 序列化
    *
    * @return 序列化后的字符串
    */
    std::string serializeSelf()
    {
        std::ostringstream os;
        boost::archive::binary_oarchive oa(os);
        oa << *this;
        return os.str();
    }

    /**
    * @brief deserializeSelf 反序列化
    *
    * @param content 需要序列化的字符串mZ    
    */
    void deserializeSelf(const std::string& content)
    {
        std::istringstream is(content);
        boost::archive::binary_iarchive ia(is);
        ia >> *this;
    }

    unsigned int m_messageType;     ///< 消息类型
    std::string m_data;             ///< 消息内容
};

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        void serialize(Archive& ar, Message& message, const unsigned int version)
        {
            (void)version;
            ar & message.m_messageType;
            ar & message.m_data;
        }
    }
}

#endif
