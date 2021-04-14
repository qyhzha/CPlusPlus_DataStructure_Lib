#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

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
    bool insert(const T& obj)
    {
        return insert(this->m_size, obj);
    }

    bool insert(int i, const T& obj)
    {
        bool ret = true;

        i = i % (this->m_size + 1);

        ret = QList<T>::insert(i, obj);

        if(ret && ((i == 0) || (i == this->m_size)))
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if(i == 0)
        {
            Node* toDel = this->m_header->next;

            if(toDel != NULL)
            {
                this->m_header->next = toDel->next;
                this->m_size--;

                if(this->m_size > 0)
                {
                    last_to_first();

                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = QList<T>::remove(i);
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

    int find(const T& obj) const
    {
        int ret = -1;
        Node* node = this->m_header->next;

        for(int i = 0; i < this->m_size; i++)
        {
            if(node->value == obj)
            {
                ret = i;
                break;
            }

            node = node->next;
        }

        return ret;
    }

    void clear()
    {
        while(this->m_size > 1)
        {
            remove(1);
        }

        if(this->m_size == 1)
        {
            Node* toDel = this->m_header->next;

            this->m_header->next = NULL;
            this->m_size = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }
    }

    bool move(int i, int step = 1)
    {
        return QList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (this->m_size == 0) || (this->m_current == NULL);
    }

    ~QCircleList()
    {
        clear();
        delete this->temp;
    }
};

}

#endif // CIRCLELIST_H
