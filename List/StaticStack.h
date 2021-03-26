#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"

namespace QinLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_size;
    int m_top;

public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    void push(const T& obj)
    {
        if(m_size < N)
        {
            m_space[m_size] = obj;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack...");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_size--;
            m_top--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No object in current stack...");
        }
    }

    T top() const
    {
        if(m_size <= 0)
        {
            THROW_EXCEPTION(InvalidOperationException, "No object in current stack...");
        }

        return m_space[m_top];
    }

    int size() const
    {
        return m_size;
    }

    int length() const
    {
        return m_size;
    }

    int capacity() const
    {
        return N;
    }

    void clear()
    {
        m_size = 0;
        m_top = -1;
    }

    ~StaticStack()
    {

    }
};

}

#endif // STATICSTACK_H
