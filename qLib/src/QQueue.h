#ifndef __QQUEUE_H__
#define __QQUEUE_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QQueue : public QObject
{
public:
    virtual void enqueue(const T& obj) = 0;
    virtual void dequeue() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
};

}

#endif
