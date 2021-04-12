#ifndef __DUALCIRCLELIST_H__
#define __DUALCIRCLELIST_H__

#include "QDualLinkList.h"

namespace qLib 
{

template <typename T>
class DualCircleList : public QDualLinkList<T>
{
protected:
    typedef typename QDualLinkList<T>::Node Node;

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node* position_tail(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&(this->m_header));

        if(ret)
        {
            for(int p = -1; p < i; p++)
            {
                ret = ret->pre;
            }
        }

        return ret;
    }

public:
    DualCircleList()
    {
        this->m_header.pre = reinterpret_cast<Node*>(&this->m_header);
        this->m_header.next = reinterpret_cast<Node*>(&this->m_header);
    }

    T& operator [](int i)
    {
        i = mod(i);

        if((i < 0) || (i >= this->m_length))
        {
            THROW_EXCEPTION(QIndexOutOfBoundsException, "Index i out of bounds...");
        }

        return DualCircleList<T>::position(i)->value;
    }

    bool insert(const T& obj)
    {
        return insert(this->m_length, obj);
    }

    bool insert(int i, const T& obj)
    {
        bool ret = true;
        Node* node = QDualLinkList<T>::create();

        i = i % (this->m_length + 1);

        if(node != NULL)
        {
            Node* pre = this->position(i - 1);
            Node* next = pre->next;

            node->value = obj;
            pre->next = node;
            next->pre = node;
            node->next = next;
            node->pre = pre;

            this->m_length++;
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    bool insert_tail(int i, const T& obj)
    {
        bool ret = true;
        Node* node = QDualLinkList<T>::create();

        i = i % (this->m_length + 1);

        if(node != NULL)
        {
            Node* pre = this->position_tail(i);
            Node* next = pre->next;

            node->value = obj;
            pre->next = node;
            next->pre = node;
            node->next = next;
            node->pre = pre;

            this->m_length++;
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = (i >= 0) && (i < this->m_length);

        if(ret)
        {
            Node* pre = this->position(i - 1);
            Node* toDel = pre->next;
            Node* next = toDel->next;

            if(this->m_current == toDel)
            {
                this->m_current = next;
            }

            if(toDel != NULL)
            {
                pre->next = next;
                next->pre = pre;
                this->m_length--;

                QDualLinkList<T>::destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    bool set(int i, const T& obj)
    {
        return QDualLinkList<T>::set(mod(i), obj);
    }

    bool get(int i, T& obj) const
    {
        return QDualLinkList<T>::get(mod(i), obj);
    }

    T get(int i) const
    {
        return QDualLinkList<T>::get(mod(i));
    }

    void clear()
    {
        while(this->m_length > 0)
        {
            remove(0);
        }

        this->m_current = NULL;
    }

    bool move(int i, int step = 1) const
    {
        return QDualLinkList<T>::move(mod(i), step);
    }

    bool end() const
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    bool next() const
    {
        int i = 0;
        while((i < this->m_step) && !end())
        {
            const_cast<DualCircleList<T>&>(*this).m_current = this->m_current->next;

            if(this->m_current != reinterpret_cast<Node*>(&this->m_header))
            {
                i++;
            }
        }

        if(this->m_current == reinterpret_cast<Node*>(&this->m_header))
        {
            const_cast<DualCircleList<T>&>(*this).m_current = this->m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre() const
    {
        int i = 0;
        while((i < this->m_step) && !end())
        {
            const_cast<DualCircleList<T>&>(*this).m_current = this->m_current->pre;

            if(this->m_current != reinterpret_cast<Node*>(&this->m_header))
            {
                i++;
            }
        }

        if(this->m_current == reinterpret_cast<Node*>(&this->m_header))
        {
            const_cast<DualCircleList<T>&>(*this).m_current = this->m_current->pre;
        }

        return (i == this->m_step);
    }

    int find(const T& obj) const
    {
        int ret = -1;
        Node* node = this->m_header.next;

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

    ~DualCircleList()
    {
        clear();
    }
};

}

#endif // DUALCIRCLELIST_H
