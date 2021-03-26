#ifndef STACK_H
#define STACK_H

#include "Object.h"
#include "Exception.h"

namespace QinLib
{

template <typename T>
class Stack : public Object
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
