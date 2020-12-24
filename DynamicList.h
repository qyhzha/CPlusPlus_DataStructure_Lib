#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include <cstdlib>

namespace QinLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];
        if(this->m_array != NULL)
        {
            m_capacity = capacity;
            this->m_length = 0;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create dynamiclist object...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T* m_temp = m_array;
            m_array = new T[capacity];
            if(m_array != NULL)
            {
                int length = (m_length < capacity) ? m_length : capacity;

                for(int i = 0; i < length; i++)
                {
                    m_array[i] = m_temp[i];
                }

                m_capacity = capacity;
                m_length = length;

                delete[] m_temp;
            }
            else
            {
                m_array = m_tempptr;
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to resize dynamiclist object...");
            }
        }
    }

    ~DynamicList()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
