#ifndef __QABSTRACTLIST_H__
#define __QABSTRACTLIST_H__

#include "QObject.h"

namespace qLib
{

template <typename T>
class QAbstractList : public QObject
{
    protected:
        int m_length;

    public:
        virtual int length() const
        {
            return m_length;
        }

        virtual int size() const
        {
            return m_length;
        }

        virtual bool isEmpty() const
        {
            return (m_length == 0);
        }

        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool set(int i, const T &e) = 0;
        virtual bool get(int i, T &e) const = 0;
        virtual void clear() = 0;
};

}

#endif
