#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace QinLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

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

        ret = LinkList<T>::insert(i, obj);

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
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T& obj)
    {
        return LinkList<T>::set(mod(i), obj);
    }

    bool get(int i, T& obj) const
    {
        return LinkList<T>::get(mod(i), obj);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
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
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList()
    {
        clear();
        delete this->temp;
    }
};

}

#endif // CIRCLELIST_H
