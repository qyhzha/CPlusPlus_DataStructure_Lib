#ifndef __QLIST_H__
#define __QLIST_H__

#include "QObject.h"
#include "QAbstractList.h"
#include "QException.h"
#include <cstdlib>

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
        Node *m_current;
        int m_step;

        Node *position(int i) const
        {
            Node *ret = m_header;

            for (int p = -1; p < i; p++)
            {
                ret = ret->next;
            }

            return ret;
        }

        virtual Node *createNode()
        {
            return new Node();
        }

        virtual void destroyNode(Node *node)
        {
            delete node;
        }
    public:
        QList()
        {
            this->m_header = reinterpret_cast<Node *>(malloc(sizeof(Node)));
            this->m_current = NULL;
            this->m_size = 0;
            this->m_step = 1;

            if (this->m_header == NULL)
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QList Note object.");
                return;
            }

            this->m_header->next = NULL;
        }

        ~QList()
        {
            clear();
            free(this->m_header);
        }

        bool insert(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i <= this->m_size));

            if (ret)
            {
                Node *node = createNode();

                if (node == NULL)
                {
                    THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert new node...");
                    return false;
                }

                Node *current = position(i - 1);

                node->value = e;
                node->next = current->next;
                current->next = node;

                this->m_size++;
            }

            return ret;
        }

        bool insert(const T &obj)
        {
            return insert(this->m_size, obj);
        }

        bool remove(int i)
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                Node *current = position(i - 1);
                Node *toDel = current->next;

                if (this->m_current == toDel)
                {
                    this->m_current = toDel->next;
                }

                current->next = toDel->next;
                this->m_size--;

                destroyNode(toDel);
            }

            return ret;
        }

        bool remove()
        {
            return remove(this->m_size - 1);
        }

        bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                position(i)->value = e;
            }

            return ret;
        }

        bool get(int i, T &e) const
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                e = position(i)->value;
            }

            return ret;
        }

        virtual T get(int i) const
        {
            T ret;

            if (get(i, ret) != true)
            {
                THROW_EXCEPTION(QInvalidParameterException, "Paramter is invalid.");
            }

            return ret;
        }

        void clear()
        {
            while (this->m_size > 0)
            {
                remove(0);
            }
        }

        virtual bool move(int i, int step = 1) const
        {
            bool ret = (i >= 0) && (i < this->m_size) && (step > 0);

            if (ret)
            {
                const_cast<QList<T>&>(*this).m_current = position(i);
                const_cast<QList<T>&>(*this).m_step = step;
            }

            return ret;
        }

        virtual bool end() const
        {
            return (this->m_current == NULL);
        }

        virtual T current() const
        {
            if (end())
            {
                THROW_EXCEPTION(QInvalidOperationException, "No value at current position...");
                T ret;
                return ret;
            }

            return m_current->value;
        }

        virtual bool next() const
        {
            int i = 0;
            while ((i < m_step) && !end())
            {
                const_cast<QList<T>&>(*this).m_current = m_current->next;
                i++;
            }

            return (i == m_step);
        }

        virtual int find(const T &obj) const
        {
            int ret = -1;
            int i = 0;

            Node *node = m_header->next;

            while (node != NULL)
            {
                if (node->value == obj)
                {
                    ret = i;
                    break;
                }

                i++;
                node = node->next;
            }

            return ret;
        }
};

}

#endif
