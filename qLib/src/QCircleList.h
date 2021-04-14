#ifndef __QCIRCLELIST_H__
#define __QCIRCLELIST_H__

#include "QList.h"

namespace qLib
{

template <typename T>
class QCircleList : public QList<T>
{
protected:
    typedef typename QList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_size - 1);
    }

    void last_to_first() const
    {
        last()->next = this->m_header->next;
    }

    int mod(int i) const
    {
        return (this->m_size == 0) ? 0 : (i % this->m_size);
    }

public:
    bool insert(int i, const T& obj)
    {
        bool ret = true;

        i = i % (this->m_size + 1);

        ret = QList<T>::insert(i, obj);

        if(ret && ((i == 0) || (i == this->m_size - 1)))
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = QList<T>::remove(i);

        if(ret && (i == 0))
        {
            last_to_first();
        }

        if (ret && (this->m_size == 0))
        {
            this->m_current = NULL;
        }

        return ret;
    }

    bool set(int i, const T& obj)
    {
        return QList<T>::set(mod(i), obj);
    }

    bool get(int i, T& obj) const
    {
        return QList<T>::get(mod(i), obj);
    }

    T get(int i) const
    {
        return QList<T>::get(mod(i));
    }

    bool move(int i, int step = 1)
    {
        return QList<T>::move(mod(i), step);
    }
};

}

#endif // CIRCLELIST_H
