#ifndef __QCONTAINER_H__
#define __QCONTAINER_H__

#include "QObject.h"

namespace qLib
{
template <typename T>
class QContainer : public QObject
{
    protected:
        T *m_space;
        int m_size;

    public:
        virtual int size() const
        {
            return m_size;
        }

        virtual int capacity() const
        {
            return m_size;
        }

        virtual bool isEmpty() const
        {
            return (m_size == 0);
        }

        virtual T *data() const
        {
            return m_space;
        }

        virtual const T *constData() const
        {
            return m_space;
        }

        virtual void resize(int size) = 0;

        virtual bool set(int i, const T &e) = 0;
        virtual bool get(int i, T &e) const = 0;
        virtual T get(int i) const = 0;
};

}

#endif
