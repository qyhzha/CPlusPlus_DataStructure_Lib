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
            QAbstractList<T>::destroyNode();;
        }

    public:
        QDualList()
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
            this->m_header->pre = NULL;
        }

        ~QDualList()
        {
            clear();
            free(this->m_header);
        }

        bool insert(const T &obj)
        {
            return insert(this->m_size, obj);
        }

        bool insert(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i <= this->m_size));

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

                    this->m_size++;
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
            bool ret = ((i >= 0) && (i < this->m_size));

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

                this->m_size--;

                destroy(toDel);
            }

            return ret;
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
                e = const_cast<QDualLinkList<T>&>(*this).position(i)->value;
            }

            return ret;
        }

        T get(int i) const
        {
            return const_cast<QDualLinkList<T>&>(*this)[i];
        }

        virtual bool pre() const
        {
            int i = 0;
            while ((i < m_step) && !end())
            {
                this->m_current = m_current->pre;
                i++;
            }

            return (i == m_step);
        }
};

}

#endif // DUALLINKLIST_H
