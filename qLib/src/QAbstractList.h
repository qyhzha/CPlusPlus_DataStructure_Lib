#ifndef __QABSTRACTLIST_H__
#define __QABSTRACTLIST_H__

#include "QContainer.h"

namespace qLib
{

template <typename T>
class QAbstractList : public QContainer<T>
{
    protected:
        struct Node : public QObject
        {
            T value;
            Node *next;
        };

        Node *m_header;
        mutable Node *m_current;
        mutable int m_step;

        virtual Node *position(int i) const
        {
            Node *ret = m_header;

            for (int p = -1; (p < i) && ret; p++)
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

        QAbstractList(const QAbstractList<T> &obj);
        QAbstractList &operator==(const QAbstractList<T> &obj);

    public:
        QAbstractList()
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

        ~QAbstractList()
        {
            clear();

            if (this->m_header)
            {
                free(this->m_header);
            }
        }

        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool insert(const T &e) = 0;
        virtual bool remove() = 0;

        virtual void clear()
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
                this->m_current = position(i);
                this->m_step = step;
            }

            return ret;
        }

        virtual bool end() const
        {
            return (this->m_size == 0) || (this->m_current == NULL);
        }

        virtual T current() const
        {
            if (end())
            {
                THROW_EXCEPTION(QInvalidOperationException, "No value at current position...");
                T ret;
                return ret;
            }

            return this->m_current->value;
        }

        virtual bool next() const
        {
            int i = 0;
            while ((i < this->m_step) && !end())
            {
                this->m_current = this->m_current->next;
                i++;
            }

            return (i == this->m_step);
        }

        virtual int find(const T &obj) const
        {
            int ret = -1;
            Node *node = this->m_header->next;

            for(int i = 0; (i < this->m_size) && node; i++)
            {
                if (node->value == obj)
                {
                    ret = i;
                    break;
                }

                node = node->next;
            }

            return ret;
        }
};

}

#endif
