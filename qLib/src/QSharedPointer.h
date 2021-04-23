#ifndef __QSHAREDPOINTER_H__
#define __QSHAREDPOINTER_H__

#include <cstdlib>
#include "QPointer.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QSharedPointer : public QPointer<T>
{
    protected:
        int *m_number;

        void assign(const QSharedPointer<T> &obj)
        {
            this->m_number = obj.m_number;
            this->m_pointer = obj.m_pointer;

            if (this->m_number)
            {
                (*(this->m_number))++;
            }
        }

    public:
        QSharedPointer(T *p = NULL)
        {
            this->m_pointer = NULL;
            this->m_number = NULL;

            if (p != NULL)
            {
                this->m_number = static_cast<int *>(malloc(sizeof(int)));
                if (this->m_number == NULL)
                {
                    THROW_EXCEPTION(QNoEnoughMemoryException, "No Enough Memory to Create SharadPointer QObject!");
                    return;
                }

                *(this->m_number) = 1;
                this->m_pointer = p;
            }
        }

        QSharedPointer(const QSharedPointer<T> &obj) : QPointer<T>(NULL)
        {
            assign(obj);
        }

        QSharedPointer &operator= (const QSharedPointer<T> &obj)
        {
            if (this != &obj)
            {
                clear();
                assign(obj);
            }

            return *this;
        }

        void clear()
        {
            T *pointer = this->m_pointer;
            int *number = this->m_number;

            this->m_number = NULL;
            this->m_pointer = NULL;

            if (number)
            {
                (*(number))--;

                if (*(number) == 0)
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
bool operator ==(const QSharedPointer<T> &obj1, const QSharedPointer<T> &obj2)
{
    return (obj1.get() == obj2.get());
}

template <typename T>
bool operator !=(const QSharedPointer<T> &obj1, const QSharedPointer<T> &obj2)
{
    return !(obj1 == obj2);
}

}

#endif
