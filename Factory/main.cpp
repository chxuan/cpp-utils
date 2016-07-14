#include <iostream>
#include <string>
#include "Message.hpp"
#include "Factory.hpp"

struct PersonMessage : public Message
{
    PersonMessage() {}
    PersonMessage(int id, const std::string& name, const std::string& address)
        : m_id(id), m_name(name), m_address(address) {}

    void func() override
    {
        std::cout << "id: " << m_id << std::endl;
        std::cout << "name: " << m_name << std::endl;
        std::cout << "address: " << m_address << std::endl;
    }

private:
    int m_id = 0;
    std::string m_name;
    std::string m_address;
};

int main()
{
    const int messageType = 1000;
    Factory::registerMessage<PersonMessage>(messageType, 100, "Jack", "Chengdu");
    auto p = Factory::getUnique(messageType);
    p->func();
    return 0;
}
