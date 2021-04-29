#ifndef __QSTACK_H__
#define __QSTACK_H__

#include "QList.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QStack : public QList<T>
{
    public:
        inline void push(const T &obj) { QList<T>::pushFront(obj); }
        inline T pop()
        {
            if (QList<T>::length() <= 0)
            {
                THROW_EXCEPTION(QInvalidOperationException, "No item in current stack.");
            }
            T ret = QList<T>::front();
            QList<T>::popFront();
            return ret;
        }
        inline T &top()
        {
            if (QList<T>::length() <= 0)
            {
                THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
            }
            return QList<T>::front();
        }
        inline const T &top() const { return const_cast<QStack<T> &>(*this).top(); }
};

}

#endif
