#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__

#include "QArray.h"

namespace qLib
{

template <typename T, int N>
class QStaticQArray : public QArray<T>
{
protected:
    T m_space[N];
public:
    QStaticQArray()
    {
        this->m_array = m_space;
    }

    QStaticQArray(const QStaticQArray<T, N>& e)
    {
        this->m_array = m_space;

        for(int i = 0; i < N; i++)
        {
            m_space[i] = e.m_space[i];
        }
    }

    QStaticQArray& operator =(const QStaticQArray<T, N>& e)
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
