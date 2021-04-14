#ifndef __QDUALLIST_H__
#define __QDUALLIST_H__

#include "QAbstractList.h"

namespace qLib
{

template <typename T>
class QDualLinkList : public QAbstractList<T>
{
    protected:
        struct Node : public QAbstractList<T>::Node
        {
            Node *pre;
        };

        Node *position(int i) const
        {
            return QAbstractList<T>::position(i);
        }

        Node *createNode()
        {
            return QAbstractList<T>::createNode();
        }

        void destroyNode(Node *node)
        {
            return QAbstractList<T>::destroyNode();;
        }

    public:
        QDualLinkList()
        {
            m_header.next = NULL;
            m_length = 0;
            m_step = 1;
            m_current = NULL;
        }

        virtual T &operator [](int i)
        {
            if ((i < 0) || (i >= m_length))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Index i out of bounds...");
            }

            return position(i)->value;
        }

        bool insert(const T &obj)
        {
            return insert(m_length, obj);
        }

        bool insert(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i <= m_length));

            if (ret)
            {
                Node *node = create();

                if (node != NULL)
                {
                    Node *current = position(i - 1);
                    Node *next = current->next;

                    node->value = e;
                    node->next = next;
                    current->next = node;

                    if (i == 0)
                    {
                        node->pre = NULL;
                    }
                    else
                    {
                        node->pre = current;
                    }

                    if (next != NULL)
                    {
                        next->pre = node;
                    }

                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(QNoEnoughMemoryException,
                                    "No enough memory to insert new node...");
                }
            }

            return ret;
        }

        bool remove(int i)
        {
            bool ret = ((i >= 0) && (i < m_length));

            if (ret)
            {
                Node *current = position(i - 1);
                Node *toDel = current->next;
                Node *next = toDel->next;

                if (m_current == toDel)
                {
                    m_current = next;
                }

                current->next = next;

                if (next != NULL)
                {
                    next->pre = toDel->pre;
                }

                m_length--;

                destroy(toDel);
            }

            return ret;
        }

        bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < m_length));

            if (ret)
            {
                position(i)->value = e;
            }

            return ret;
        }

        bool get(int i, T &e) const
        {
            bool ret = ((i >= 0) && (i < m_length));

            if (ret)
            {
                e = const_cast<QDualLinkList<T>&>(*this).position(i)->value;
            }

            return ret;
        }

        virtual T get(int i) const
        {
            return const_cast<QDualLinkList<T>&>(*this)[i];
        }

        int length() const
        {
            return m_length;
        }

        void clear()
        {
            while (m_length > 0)
            {
                remove(0);
            }
        }

        virtual bool move(int i, int step = 1) const
        {
            bool ret = (i >= 0) && (i < m_length) && (step > 0);

            if (ret)
            {
                const_cast<QDualLinkList<T> &>(*this).m_current = position(i);
                const_cast<QDualLinkList<T> &>(*this).m_step = step;
            }

            return ret;
        }

        virtual bool end() const
        {
            return (m_current == NULL);
        }

        virtual T current() const
        {
            if (end())
            {
                THROW_EXCEPTION(QInvalidOperationException, "No value at current position...");
            }

            return m_current->value;
        }

        virtual bool next() const
        {
            int i = 0;
            while ((i < m_step) && !end())
            {
                const_cast<QDualLinkList<T> &>(*this).m_current = m_current->next;
                i++;
            }

            return (i == m_step);
        }

        virtual bool pre() const
        {
            int i = 0;
            while ((i < m_step) && !end())
            {
                const_cast<QDualLinkList<T> &>(*this).m_current = m_current->pre;
                i++;
            }

            return (i == m_step);
        }

        virtual int find(const T &obj) const
        {
            int ret = -1;
            int i = 0;

            Node *node = m_header.next;

            while (node != NULL)
            {
                if (node->value == obj)
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

        ~QDualLinkList()
        {
            clear();
        }
};

}

#endif // DUALLINKLIST_H
