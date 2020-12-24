#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace QinLib
{

template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;

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
            THROW_EXCEPTION(InvalidOperationException, "No object in current stack...");
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
            THROW_EXCEPTION(InvalidOperationException, "No object in current stack...");
        }

        return m_list.get(0);
    }
};

}

#endif // LINKSTACK_H
