#ifndef __QLINKQUEUE_H__
#define __QLINKQUEUE_H__

#include "QQueue.h"
#include "QDualCircleList.h"

namespace qLib
{

template <typename T>
class QLinkQueue : QQueue<T>
{
protected:
    QDualCircleList<T> m_list;

public:
    void enqueue(const T& obj)
    {
        m_list.insertTail(0, obj);
    }

    void dequeue()
    {
        if(m_list.length() <= 0)
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object to delete in current queue...");
        }

        m_list.remove(0);
    }

    T front() const
    {
        if(m_list.length() <= 0)
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object to delete in current queue...");
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

#endif
