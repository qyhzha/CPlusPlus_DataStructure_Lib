#ifndef __STATICQUEUE_H__
#define __STATICQUEUE_H__

#include "QQueue.h"

namespace qLib
{

template <typename T, int N>
class QStaticQueue : public QQueue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;

public:
    QStaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    void enqueue(const T& obj)
    {
        if(m_length < N)
        {
            m_space[m_rear] = obj;
            m_rear = (m_rear + 1) % N;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(QInvalidOperationException, "No space to insert object in current queue...");
        }
    }

    void dequeue()
    {
        if(m_length > 0)
        {
            m_front = (m_front + 1) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object to delete in current queue...");
        }
    }

    T front() const
    {
        if(m_length <= 0)
        {
            THROW_EXCEPTION(QInvalidOperationException, "No object in current queue...");
        }

        return m_space[m_front];
    }

    void clear()
    {
        m_length = 0;
        m_front = 0;
        m_rear = 0;
    }

    int length() const
    {
        return m_length;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif // STATICQUEUE_H
