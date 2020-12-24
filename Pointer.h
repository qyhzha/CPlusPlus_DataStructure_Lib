#ifndef POINTER_H
#define POINTER_H

#include "Object.h"
#include "Exception.h"

namespace QinLib
{
template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer()
    {
        m_pointer = NULL;
    }

    Pointer(T* p)
    {
        m_pointer = p;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    const T* operator ->() const
    {
        return m_pointer;
    }

    const T& operator *() const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == NULL);
    }

    T* get() const
    {
        return m_pointer;
    }

    virtual ~Pointer() = 0;
};
}

namespace QinLib
{
template <typename T>
Pointer<T>::~Pointer()
{

}
}

#endif // POINTER_H
