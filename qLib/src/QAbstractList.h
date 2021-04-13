#ifndef __QABSTRACTLIST_H__
#define __QABSTRACTLIST_H__

#include "QContainer.h"

namespace qLib
{

template <typename T>
class QAbstractList : public QContainer<T>
{
    public:
        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual void clear() = 0;
        virtual bool insert(const T &e) = 0;
        virtual bool remove() = 0;
};

}

#endif
