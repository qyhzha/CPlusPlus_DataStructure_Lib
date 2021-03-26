#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"

namespace QinLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_number;

    void assign(const SharedPointer<T>& obj)
    {
        m_number = obj.m_number;

        if(m_number)
        {
            (*m_number)++;
        }

        this->m_pointer = obj.m_pointer;
    }
public:
    SharedPointer(T* p = NULL)
    {
        if(p != NULL)
        {
            m_number = static_cast<int*>(malloc(sizeof(int)));

            if(m_number != NULL)
            {
                *m_number = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory to Create SharadPointer Object!");
            }
        }
        else
        {
            m_number = NULL;
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer& operator = (const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        T* pointer = this->m_pointer;
        int* number = this->m_number;

        this->m_number = NULL;
        this->m_pointer = NULL;

        if(number)
        {
            (*number)--;

            if(*number == 0)
            {
                free(number);
                delete pointer;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator ==(const SharedPointer<T>& obj1, const SharedPointer<T>& obj2)
{
    return (obj1.m_pointer == obj2.m_pointer);
}

template <typename T>
bool operator !=(const SharedPointer<T>& obj1, const SharedPointer<T>& obj2)
{
    return !(obj1 == obj2);
}

}

#endif // SHAREDPOINTER_H
