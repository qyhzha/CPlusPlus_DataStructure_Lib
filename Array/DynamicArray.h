#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"

namespace QinLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int len, int newlen)
    {
        T* ret = new T[newlen];

        if(ret != NULL)
        {
            for(int i = 0; (i < len) && (i < newlen); i++)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete temp;
        }
    }
public:
    DynamicArray(int length)
    {
        this->m_array = new T[length];

        if(this->m_array != NULL)
        {
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create dynamicarray object...");
        }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray& operator = (const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }
    }

    void resize(int length)
    {
        if(m_length != length)
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }

    int length() const
    {
        return m_length;
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
