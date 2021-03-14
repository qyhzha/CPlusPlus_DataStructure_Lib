#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace QinLib
{

template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    StaticArray(const StaticArray<T, N>& e)
    {
        this->m_array = m_space;

        for(int i = 0; i < N; i++)
        {
            m_space[i] = e.m_space[i];
        }
    }

    StaticArray& operator =(const StaticArray<T, N>& e)
    {
        if(this != &e)
        {
            for(int i = 0; i < N; i++)
            {
                m_space[i] = e.m_space[i];
            }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
