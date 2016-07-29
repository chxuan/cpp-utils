#ifndef _RANGE_H
#define _RANGE_H

#include <iostream>
#include <exception>

template<typename T>
class RangeImpl
{
    class Iterator;
public:
    RangeImpl(T begin, T end, T step = 1) : m_begin(begin), m_end(end), m_step(step)
    {
        if (step > 0 && m_begin >= m_end)
        {
            throw std::logic_error("end must greater than begin.");
        }
        else if (step < 0 && m_begin <= m_end)
        {
            throw std::logic_error("end must less than begin.");
        }

        m_stepEnd = (m_end - m_begin) / m_step;
        if (m_begin + m_stepEnd * m_step != m_end)
        {
            ++m_stepEnd;
        }
    }

    Iterator begin()
    {
        return Iterator(0, *this);
    }

    Iterator end()
    {
        return Iterator(m_stepEnd, *this);
    }

    T operator[](int i)
    {
        return m_begin + i * m_step;
    }

    int size() const
    {
        return m_stepEnd;
    }

private:
    T m_begin;
    T m_end;
    T m_step;
    int m_stepEnd = 0;

private:
    class Iterator
    {
    public:
        Iterator(int start, RangeImpl& range) : m_currentStep(start), m_range(range)
        {
            m_currentValue = m_range.m_begin + m_currentStep * m_range.m_step;
        }

        T operator*()
        {
            return m_currentValue;
        }

        const Iterator* operator++()
        {
            m_currentValue += m_range.m_step;
            m_currentStep++;
            return this;
        }

        const Iterator* operator--()
        {
            m_currentValue -= m_range.m_step;
            m_currentStep--;
            return this;
        }

        bool operator=(const Iterator& other)
        {
            return m_currentStep == other.m_currentStep;
        }

        bool operator!=(const Iterator& other)
        {
            return m_currentStep != other.m_currentStep;
        }

    private:
        T m_currentValue;
        int m_currentStep = 0;
        RangeImpl& m_range;
    };
};

template<typename T, typename V>
auto range(T begin, T end, V stepSize)->RangeImpl<decltype(begin + end + stepSize)>
{
    return RangeImpl<decltype(begin + end + stepSize)>(begin, end, stepSize);
}

template<typename T>
RangeImpl<T> range(T begin, T end)
{
    return RangeImpl<T>(begin, end, 1);
}

template<typename T>
RangeImpl<T> range(T end)
{
    return RangeImpl<T>(T(), end, 1);
}

#endif
