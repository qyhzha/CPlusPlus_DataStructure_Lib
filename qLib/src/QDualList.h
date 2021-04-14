#ifndef __QDUALLIST_H__
#define __QDUALLIST_H__

#include "QAbstractList.h"
#include "QException.h"
#include <cstdlib>

namespace qLib
{

template <typename T>
class QDualList : public QAbstractList<T>
{
    protected:
        typedef typename QAbstractList<T>::Node Node;

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
        }

        ~QDualList()
        {
            clear();
            if (this->m_header)
            {
                free(this->m_header);
            }
        }

        bool insert(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i <= this->m_size));

            if (ret)
            {
                Node *node = QAbstractList<T>::createNode();

                if (node == NULL)
                {
                    THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert new node...");
                    return false;
                }

                Node *current = QAbstractList<T>::position(i - 1);
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
                Node *current = QAbstractList<T>::position(i - 1);
                Node *toDel = current->next;
                Node *next = toDel->next;

                if (this->m_current == toDel)
                {
                    this->m_current = next;
                }

                current->next = next;

                if (next != NULL)
                {
                    next->pre = toDel->pre;
                }

                this->m_size--;

                QAbstractList<T>::destroyNode(toDel);
            }

            return ret;
        }

        bool remove()
        {
            return remove(this->m_size - 1);
        }

        void clear()
        {
            while(this->m_size > 0)
            {
                remove(0);
            }
        }

        virtual bool pre() const
        {
            int i = 0;
            while ((i < this->m_step) && !QAbstractList<T>::end())
            {
                this->m_current = this->m_current->pre;
                i++;
            }

            return (i == this->m_step);
        }
};

}

#endif
