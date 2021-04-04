#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__

#include <cstdlib>
#include "QPointer.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QSharedPointer : public QPointer<T>
{
protected:
    int* m_number;

    void assign(const QSharedPointer<T>& obj)
    {
        m_number = obj.m_number;

        if(m_number)
        {
            (*m_number)++;
        }

        this->m_pointer = obj.m_pointer;
    }
public:
    QSharedPointer(T* p = NULL)
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
                THROW_EXCEPTION(QNoEnoughMemoryException, "No Enough Memory to Create SharadPointer QObject!");
            }
        }
        else
        {
            m_number = NULL;
        }
    }

    QSharedPointer(const QSharedPointer<T>& obj) : QPointer<T>(NULL)
    {
        assign(obj);
    }

    QSharedPointer& operator = (const QSharedPointer<T>& obj)
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

    ~QSharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator ==(const QSharedPointer<T>& obj1, const QSharedPointer<T>& obj2)
{
    return (obj1.m_pointer == obj2.m_pointer);
}

template <typename T>
bool operator !=(const QSharedPointer<T>& obj1, const QSharedPointer<T>& obj2)
{
    return !(obj1 == obj2);
}

}

#endif // SHAREDPOINTER_H
