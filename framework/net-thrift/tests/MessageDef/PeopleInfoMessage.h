#ifndef _PEOPLEINFOMESSAGE_H
#define _PEOPLEINFOMESSAGE_H

#include "MessageDefHead.h"

class QueryPeopleInfoMessage
{
public:
    std::string serializeSelf()
    {
        std::ostringstream os;
        boost::archive::binary_oarchive oa(os);
        oa << *this;
        return os.str();
    }

    void deserializeSelf(const std::string& content)
    {
        std::istringstream is(content);
        boost::archive::binary_iarchive ia(is);
        ia >> *this;
    }

    std::string m_cardId;
};

namespace boost
{
    namespace serialization
    {
        template <class Archive>
        void serialize(Archive& ar, QueryPeopleInfoMessage& message, const unsigned int version)
        {
            (void)version;
            ar & message.m_cardId;
        }
    }
}

class Cat
{
public:
    std::string m_name;
    int m_age;
};

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        void serialize(Archive& ar, Cat& message, const unsigned int version)
        {
            (void)version;
            ar & message.m_name;
            ar & message.m_age;
        }
    }
}

class PeopleInfoMessage
{
public:
    std::string serializeSelf()
    {
        std::ostringstream os;
        boost::archive::binary_oarchive oa(os);
        oa << *this;
        return os.str();
    }

    void deserializeSelf(const std::string& content)
    {
        std::istringstream is(content);
        boost::archive::binary_iarchive ia(is);
        ia >> *this;
    }

    std::string m_name;
    unsigned int m_age;
    unsigned int m_sex;
    std::vector<Cat> m_cats;
};

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        void serialize(Archive& ar, PeopleInfoMessage& message, const unsigned int version)
        {
            (void)version;
            ar & message.m_name;
            ar & message.m_age;
            ar & message.m_sex;
            ar & message.m_cats;
        }
    }
}

#endif
