#ifndef _CONNECT_H
#define _CONNECT_H

#include <vector>
#include <functional>

#define emit
#define slots
#define signals public
#define connect(sender, signal, receiver, slot) ((sender)->signal.bind(receiver, slot))

template<typename T1>
class SlotBase
{
public:
    virtual ~SlotBase() {}
    virtual void exec(T1 t1) = 0;
};

template<typename T, typename T1>
class SlotImpl : public SlotBase<T1>
{
public:
    SlotImpl(T* receiver, void (T::*func)(T1))
    {
        m_receiver = receiver;
        m_func = func;
    }

    virtual void exec(T1 t1)
    {
        (m_func->*m_func)(t1);
    }

private:
    T* m_receiver = nullptr;
    void (T::*m_func)(T1);
};

template<typename T1>
class Slot
{
public:
    template<typename T>
    Slot(T* receiver, void (T::*func)(T1))
    {
        m_slotBase = new SlotImpl<T, T1>(receiver, func); 
    }

    ~Slot()
    {
        delete m_slotBase;
        m_slotBase = NULL;
    }

    void exec(T1 t1)
    {
        m_slotBase->exec(t1);
    }

private:
    SlotBase<T1>* m_slotBase;
};

#endif
