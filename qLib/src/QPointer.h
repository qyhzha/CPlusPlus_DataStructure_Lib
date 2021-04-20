#ifndef __QPOINTER_H__
#define __QPOINTER_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{
template <typename T>
class QPointer : public QObject
{
    protected:
        T *m_pointer;

    public:
        QPointer()
        {
            m_pointer = NULL;
        }

        QPointer(T *p)
        {
            m_pointer = p;
        }

        QPointer(const QPointer &obj)
        {
            m_pointer = obj.m_pointer;
        }

        virtual ~QPointer() = 0;

        T *operator ->()
        {
            return m_pointer;
        }

        T &operator *()
        {
            return *m_pointer;
        }

        const T *operator ->() const
        {
            return m_pointer;
        }

        const T &operator *() const
        {
            return *m_pointer;
        }

        bool isNull() const
        {
            return (m_pointer == NULL);
        }

        T *get() const
        {
            return m_pointer;
        }
};

}

namespace qLib
{

template <typename T> QPointer<T>::~QPointer()
{

}

}

#endif
