#ifndef __QVECTOR_H__
#define __QVECTOR_H__

#include "QObject.h"

namespace qLib
{

template <typename T>
class QVector : public QObject
{
    protected:
        T *m_space;
        int m_size;

    public:
        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool set(int i, const T &e) = 0;
        virtual bool get(int i, T &e) const = 0;
        virtual int length() const = 0;
        virtual void clear() = 0;
};

}

#endif