#ifndef __QLINKSTACK_H__
#define __QLINKSTACK_H__

#include "QStack.h"
#include "QList.h"

namespace qLib
{

template <typename T>
class QLinkQStack : public QStack<T>
{
protected:
    QList<T> m_list;

public:
    void push(const T& obj)
    {
        m_list.insert(0, obj);
    }

    void pop()
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int size() const
    {
         return m_list.length();
    }

    T top() const
    {
        if(m_list.length() <= 0)
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
        }

        return m_list.get(0);
    }
};

}

#endif
