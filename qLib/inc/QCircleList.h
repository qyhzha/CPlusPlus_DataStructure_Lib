#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

#include "QLinkList.h"

namespace qLib
{

template <typename T>
class QCircleList : public QLinkList<T>
{
protected:
    typedef typename QLinkList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_length - 1);
    }

    void last_to_first() const
    {
        last()->next = this->m_header->next;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    bool insert(const T& obj)
    {
        return insert(this->m_length, obj);
    }

    bool insert(int i, const T& obj)
    {
        bool ret = true;

        i = i % (this->m_length + 1);

        ret = QLinkList<T>::insert(i, obj);

        if(ret && ((i == 0) || (i == this->m_length)))
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
                this->m_length--;

                if(this->m_length > 0)
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
            ret = QLinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T& obj)
    {
        return QLinkList<T>::set(mod(i), obj);
    }

    bool get(int i, T& obj) const
    {
        return QLinkList<T>::get(mod(i), obj);
    }

    T get(int i) const
    {
        return QLinkList<T>::get(mod(i));
    }

    int find(const T& obj) const
    {
        int ret = -1;
        Node* node = this->m_header->next;

        for(int i = 0; i < this->m_length; i++)
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
        while(this->m_length > 1)
        {
            remove(1);
        }

        if(this->m_length == 1)
        {
            Node* toDel = this->m_header->next;

            this->m_header->next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }
    }

    bool move(int i, int step = 1)
    {
        return QLinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~QCircleList()
    {
        clear();
        delete this->temp;
    }
};

}

#endif // CIRCLELIST_H
