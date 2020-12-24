#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace QinLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p) {}

    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_objectName = NULL;
    }

    SmartPointer& operator =(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* pointer = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_objectName = NULL;

            delete pointer;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }

};

}

#endif // SMARTPOINTER_H
