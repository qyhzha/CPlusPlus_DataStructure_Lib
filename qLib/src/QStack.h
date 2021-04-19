#ifndef __QSTACK_H__
#define __QSTACK_H__

#include "QObject.h"
#include "QList.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QStack : public QObject
{
    protected:
        QList<T> m_list;

    public:
        void push(const T &obj)
        {
            m_list.insert(0, obj);
        }

        T pop()
        {
            T ret;
            if (m_list.length() <= 0)
            {
                THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
                return ret;
            }

            ret = m_list[0];
            m_list.remove(0);

            return ret;
        }

        void clear()
        {
            m_list.clear();
        }

        int size() const
        {
            return m_list.length();
        }

        int length() const
        {
            return m_list.length();
        }

        bool isEmpty() const
        {
            return (m_list.length() == 0);
        }

        T &top()
        {
            if (m_list.length() <= 0)
            {
                THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
            }

            return m_list[0];
        }

        const T &top() const
        {
            return const_cast<QStack<T> &>(*this).top();
        }
};

}

#endif
