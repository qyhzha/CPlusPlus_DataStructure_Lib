#ifndef __STACK_H__
#define __STACK_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QStack : public QObject
{
public:
    virtual void push(const T& obj) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;
};

}

#endif // STACK_H
