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

        Node* positionTail(int i) const
        {
            Node* ret = this->m_header;

            for(int p = -1; (p < i) && ret; p++)
            {
                ret = ret->pre;
            }

            return ret;
        }

        virtual bool insert(int i, const T &e, bool isHeader)
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

                Node *current = isHeader ? QAbstractList<T>::position(i - 1) : positionTail(i - 1);

                if (isHeader)
                {
                    Node *next = current->next;

                    node->value = e;
                    node->next = next;
                    node->pre = current;
                    current->next = node;

                    if (next != NULL) next->pre = node;
                    if (i == 0) node->pre = NULL;
                    if (i == this->m_size) this->m_header->pre = node;
                }
                else
                {
                    Node *pre = current->pre;

                    node->value = e;
                    node->next = current;
                    node->pre = pre;
                    current->pre = node;

                    if (pre != NULL) pre->next = node;
                    if (i == 0) node->next = NULL;
                    if (i == this->m_size) this->m_header->next = node;
                }

                this->m_size++;
            }

            return ret;
        }

        virtual bool remove(int i, bool isHeader)
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                Node *current = isHeader ? QAbstractList<T>::position(i - 1) : positionTail(i - 1);
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

                if (i == this->m_size - 1)
                {
                    this->m_header->pre = toDel->pre;
                }

                this->m_size--;

                QAbstractList<T>::destroyNode(toDel);
            }

            return ret;
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
            if (this->m_header)
            {
                free(this->m_header);
            }
        }

        bool insert(int i, const T &obj)
        {
            return insert((i <= this->m_size / 2) ? i : (this->m_size - i), obj, (i <= this->m_size / 2));
        }

        bool insert(const T &obj)
        {
            return insert(0, obj, false);
        }

        bool remove(int i)
        {
            return remove((i <= this->m_size / 2) ? i : (this->m_size - i), (i <= this->m_size / 2));
        }

        bool remove()
        {
            return remove(0, false);
        }

        bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                if (i <= this->m_size / 2)
                {
                    QAbstractList<T>::position(i)->value = e;
                }
                else
                {
                    positionTail(this->m_size - i)->value = e;
                }
            }

            return ret;
        }

        bool get(int i, T &e) const
        {
            bool ret = ((i >= 0) && (i < this->m_size));

            if (ret)
            {
                if (i <= this->m_size / 2)
                {
                    e = QAbstractList<T>::position(i)->value;
                }
                else
                {
                    e = positionTail(this->m_size - i)->value;
                }
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

        T &operator [](int i)
        {
            if ((i < 0) || (i >= this->m_size))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Index out of bound.");
            }

            return (i <= this->m_size / 2) ? QAbstractList<T>::position(i)->value : positionTail(this->m_size - i)->value;
        }

        T operator [](int i) const
        {
            return const_cast<QDualList<T> &>(*this).operator[](i);
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
