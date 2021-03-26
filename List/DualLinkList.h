#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"

namespace QinLib
{

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* pre;
        Node* next;
    };

    mutable struct : public Object
    {
        char value[sizeof(T)];
        Node* pre;
        Node* next;
    } m_header;

    int m_length;
    int m_step;
    Node* m_current;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        if(ret)
        {
            for(int p = -1; p < i; p++)
            {
                ret = ret->next;
            }
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* node)
    {
        delete node;
    }
public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    virtual T& operator [](int i)
    {
        if((i < 0) || (i >= m_length))
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Index i out of bounds...");
        }

        return position(i)->value;
    }

    bool insert(const T& obj)
    {
        return insert(m_length, obj);
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i <= m_length));

        if(ret)
        {
            Node* node = create();

            if(node != NULL)
            {
                Node* current = position(i - 1);
                Node* next = current->next;

                node->value = e;
                node->next = next;
                current->next = node;

                if(i == 0)
                {
                    node->pre = NULL;
                }
                else
                {
                    node->pre = current;
                }

                if(next != NULL)
                {
                    next->pre = node;
                }

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert new node...");
            }
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            Node* current = position(i - 1);
            Node* toDel = current->next;
            Node* next = toDel->next;

            if(m_current == toDel)
            {
                m_current = next;
            }

            current->next = next;

            if(next != NULL)
            {
                next->pre = toDel->pre;
            }

            m_length--;

            destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            position(i)->value = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ((i >= 0) && (i < m_length));

        if(ret)
        {
            e = const_cast<DualLinkList<T>&>(*this).position(i)->value;
        }

        return ret;
    }

    virtual T get(int i) const
    {
        return const_cast<DualLinkList<T>&>(*this)[i];
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove(0);
        }
    }

    virtual bool move(int i, int step = 1) const
    {
        bool ret = (i >= 0) && (i < m_length) && (step > 0);

        if(ret)
        {
            const_cast<DualLinkList<T>&>(*this).m_current = position(i);
            const_cast<DualLinkList<T>&>(*this).m_step = step;
        }

        return ret;
    }

    virtual bool end() const
    {
        return (m_current == NULL);
    }

    virtual T current() const
    {
        if(end())
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }

        return m_current->value;
    }

    virtual bool next() const
    {
        int i = 0;
        while((i < m_step) && !end())
        {
            const_cast<DualLinkList<T>&>(*this).m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    virtual bool pre() const
    {
        int i = 0;
        while((i < m_step) && !end())
        {
            const_cast<DualLinkList<T>&>(*this).m_current = m_current->pre;
            i++;
        }

        return (i == m_step);
    }

    virtual int find(const T& obj) const
    {
        int ret = -1;
        int i = 0;

        Node* node = m_header.next;

        while(node != NULL)
        {
            if(node->value == obj)
            {
                ret = i;
                break;
            }
            else
            {
                i++;
                node = node->next;
            }
        }

        return ret;
    }

    ~DualLinkList()
    {
        clear();
    }
};

}

#endif // DUALLINKLIST_H
