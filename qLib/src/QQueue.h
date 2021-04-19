#ifndef __QQUEUE_H__
#define __QQUEUE_H__

#include "QObject.h"
#include "QException.h"
#include "QDualList.h"

namespace qLib
{

template <typename T>
class QQueue : public QObject
{
    protected:
        QDualList<T> m_list;

    public:
        void enqueue(const T &obj)
        {
            m_list.insert(obj);
        }

        T dequeue()
        {
            T ret = m_list[0];

            m_list.remove(0);

            return ret;
        }

        T &head()
        {
            return m_list[0];
        }

        const T &head() const
        {
            return m_list[0];
        }

        void clear()
        {
            m_list.clear();
        }

        int length() const
        {
            return m_list.length();
        }

        int size() const
        {
            return m_list.length();
        }

        bool isEmpty() const
        {
            return m_list.isEmpty();
        }
};

}

#endif
