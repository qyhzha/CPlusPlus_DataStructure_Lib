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
            QAbstractList<T>::clear();
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

        T get(int i) const
        {
            T ret;

            if (get(i, ret) != true)
            {
                THROW_EXCEPTION(QInvalidParameterException, "Paramter is invalid.");
            }

            return ret;
        }
};

}

#endif
