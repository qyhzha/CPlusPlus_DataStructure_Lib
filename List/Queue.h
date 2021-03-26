#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"
#include "Exception.h"

namespace QinLib
{

template <typename T>
class Queue : public Object
{
public:
    virtual void enqueue(const T& obj) = 0;
    virtual void dequeue() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
};

}

#endif // QUEUE_H
