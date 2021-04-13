#ifndef __QCONTAINER_H__
#define __QCONTAINER_H__

#include "QObject.h"

namespace qLib
{
template <typename T>
class QContainer : public QObject
{
    protected:
        int m_size;

    public:
        inline int size() const
        {
            return m_size;
        }

        inline int length() const
        {
            return m_size;
        }

        inline int capacity() const
        {
            return m_size;
        }

        inline bool isEmpty() const
        {
            return (m_size == 0);
        }

        virtual bool set(int i, const T &e) = 0;
        virtual bool get(int i, T &e) const = 0;
        virtual T get(int i) const = 0;
};

}

#endif
