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
        typedef typename QAbstractList<T>::Node Node;

    public:
        QList()
        {
            this->m_current = NULL;
            this->m_size = 0;
            this->m_step = 1;

            this->m_header = reinterpret_cast<Node *>(malloc(sizeof(Node)));
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
                Node *current = QAbstractList<T>::position(i - 1);
                Node *toDel = current->next;

                if (this->m_current == toDel)
                {
                    this->m_current = toDel->next;
                }

                current->next = toDel->next;
                this->m_size--;

                QAbstractList<T>::destroyNode(toDel);
            }

            return ret;
        }

        bool remove()
        {
            return remove(this->m_size - 1);
        }

        bool removeOne(const T &obj)
        {
            for(this->move(0); !this->end(); this->next())
            {
                T &data = this->current();

                Node *toDel = current->next;

                if (this->m_current == toDel)
                {
                    this->m_current = toDel->next;
                }

                current->next = toDel->next;
                this->m_size--;

                QAbstractList<T>::destroyNode(toDel);
            }
        }

        bool removeAll(const T &obj)
        {
            for(this->move(0); !this->end(); this->next())
            {
                if (this->current() == obj)
                {
                    delete this->current();
                }
            }
        }

        void clear()
        {
            while(this->m_size > 0)
            {
                remove(0);
            }
        }
};

}

#endif
