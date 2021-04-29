#ifndef __QQUEUE_H__
#define __QQUEUE_H__

#include "QException.h"
#include "QList.h"

namespace qLib
{

template <typename T>
class QQueue : public QList<T>
{
    public:
        inline void enqueue(const T &obj) { QList<T>::append(obj); }
        inline T dequeue() { T ret = QList<T>::first(); QList<T>::removeFirst(); return ret; }
        inline T &head()
        {
            if (QList<T>::length() <= 0)
            {
                THROW_EXCEPTION(QInvalidOperationException, "No object in current stack...");
            }
            return QList<T>::first();
        }
        inline const T &head() const { return const_cast<QQueue<T> &>(*this).head(); }
};

}

#endif
