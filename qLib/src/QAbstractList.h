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
        Node *m_current;
        int m_step;

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
        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual void clear() = 0;
        virtual bool insert(const T &e) = 0;
        virtual bool remove() = 0;
};

}

#endif
