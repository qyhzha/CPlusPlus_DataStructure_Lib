#ifndef __STATICLIST_H__
#define __STATICLIST_H__

#include "QSeqList.h"

namespace qLib
{

template <typename T, int N>
class QStaticList : public QSeqList<T>
{
protected:
    T m_space[N];
public:
    QStaticList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif // STATICLIST_H
