#ifndef __QSmartPointer_H__
#define __QSmartPointer_H__

#include "QPointer.h"

namespace qLib
{

template <typename T>
class QSmartPointer : public QPointer<T>
{
public:
    QSmartPointer(T* p = NULL) : QPointer<T>(p) {}

    QSmartPointer(const QSmartPointer<T>& obj) : QPointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<QSmartPointer<T>&>(obj).m_pointer = NULL;
    }

    QSmartPointer& operator =(const QSmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* pointer = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<QSmartPointer<T>&>(obj).m_objectName = NULL;

            if (pointer) delete pointer;
        }

        return *this;
    }

    ~QSmartPointer()
    {
        delete this->m_pointer;
    }

};

}

#endif
