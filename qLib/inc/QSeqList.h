#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include "QList.h"

namespace qLib
{

template <typename T>
class QSeqList :  public QList<T>
{
protected:
    T* m_array;
    int m_length;
public:
    bool insert(int i, const T& e)
    {
        bool ret = ((i >=0) && (i < m_length));

        ret = ret && (m_length < capacity());

        if(ret)
        {
            for(int index = m_length; index > i; index--)
            {
                m_array[index] = m_array[index - 1];
            }
            m_array[i] = e;
            m_length++;
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = (i >= 0 && i < m_length);
        if(ret)
        {
            for(int index = i + 1; index < m_length; index++)
            {
                m_array[index - 1] = m_array[index];
            }

            m_length--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = (i >= 0 && i < m_length);
        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = (i >= 0 && i < m_length;
        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    T& operator [](int i)
    {
        if(i < 0 || i >= m_length)
        {
            THROW_EXCEPTION(QIndexOutOfBoundsException, "Index out of bounds...");
        }
        return m_array[i];
    }

    T operator [](int i) const
    {
        return const_cast<QSeqList<T>&>(*this)[i];
    }

    virtual capacity() const = 0;
};

}

#endif // SEQLIST_H
