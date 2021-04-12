#ifndef __LIST_H__
#define __LIST_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{
template <typename T>
class QList : public QObject
{
    public:
        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool set(int i, const T &e) = 0;
        virtual bool get(int i, T &e) const = 0;
        virtual int length() const = 0;
        virtual void clear() = 0;
};

}

#endif // LIST_H
