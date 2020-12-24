#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "DualCircleList.h"

namespace QinLib
{

template <typename T>
class LinkQueue : Queue<T>
{
protected:
    DualCircleList<T> m_list;

public:
    void enqueue(const T& obj)
    {
        m_list.insert_tail(0, obj);
    }

    void dequeue()
    {
        if(m_list.length() <= 0)
        {
            THROW_EXCEPTION(InvalidOperationException, "No object to delete in current queue...");
        }

        m_list.remove(0);
    }

    T front() const
    {
        if(m_list.length() <= 0)
        {
            THROW_EXCEPTION(InvalidOperationException, "No object to delete in current queue...");
        }

        return m_list.get(0);
    }

    void clear()
    {
        m_list.clear();
    }

    int length() const
    {
        return m_list.length();
    }
};

}

#endif // LINKQUEUE_H
