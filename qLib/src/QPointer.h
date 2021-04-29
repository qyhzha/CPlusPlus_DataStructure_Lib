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
        inline QPointer()
        {
            m_pointer = NULL;
        }

        inline QPointer(T *p)
        {
            m_pointer = p;
        }

        inline QPointer(const QPointer &obj)
        {
            m_pointer = obj.m_pointer;
        }

        virtual ~QPointer() = 0;

        inline T *operator ->()
        {
            return m_pointer;
        }

        inline T &operator *()
        {
            return *m_pointer;
        }

        inline const T *operator ->() const
        {
            return m_pointer;
        }

        inline const T &operator *() const
        {
            return *m_pointer;
        }

        inline bool isNull() const
        {
            return (m_pointer == NULL);
        }

        inline T *get() const
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
