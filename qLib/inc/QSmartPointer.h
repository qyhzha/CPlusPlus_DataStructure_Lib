#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

#include "QPointer.h"

namespace qLib
{

template <typename T>
class SmartPointer : public QPointer<T>
{
public:
    SmartPointer(T* p = NULL) : QPointer<T>(p) {}

    SmartPointer(const SmartPointer<T>& obj) : QPointer<T>(NULL)
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
