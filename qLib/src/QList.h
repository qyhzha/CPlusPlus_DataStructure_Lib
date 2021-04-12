#ifndef __QLIST_H__
#define __QLIST_H__

#include "QAbstractList.h"
#include "QException.h"

namespace qLib
{
template <typename T>
class QList : public QAbstractList<T>
{
    protected:
        struct Node : public QObject
        {
            T value;
            Node *next;
        };

        Node *m_header;
        int m_length;
        int m_step;
        Node *m_current;

        Node *position(int i) const
        {
            Node *ret = m_header;

            for (int p = -1; p < i; p++)
            {
                ret = ret->next;
            }

            return ret;
        }

        virtual Node *create()
        {
            return new Node();
        }

        virtual void destroy(Node *node)
        {
            delete node;
        }
    public:
        QLinkList()
        {
            m_header = reinterpret_cast<Node *>(malloc(sizeof(Node)));
            m_header->next = NULL;
            m_length = 0;
            m_step = 1;
            m_current = NULL;
        }

        T &operator [](int i)
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

                    node->value = e;
                    node->next = current->next;
                    current->next = node;

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

                if (m_current == toDel)
                {
                    m_current = toDel->next;
                }

                current->next = toDel->next;
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
                e = const_cast<QLinkList<T>&>(*this).position(i)->value;
            }

            return ret;
        }

        virtual T get(int i) const
        {
            return const_cast<QLinkList<T>&>(*this)[i];
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
                const_cast<QLinkList<T>&>(*this).m_current = position(i);
                const_cast<QLinkList<T>&>(*this).m_step = step;
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
                const_cast<QLinkList<T>&>(*this).m_current = m_current->next;
                i++;
            }

            return (i == m_step);
        }

        virtual int find(const T &obj) const
        {
            int ret = -1;
            int i = 0;

            Node *node = const_cast<QLinkList<T>&>(*this).m_header->next;

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

        ~QLinkList()
        {
            clear();
            free(m_header);
        }
};

}

#endif // LIST_H
