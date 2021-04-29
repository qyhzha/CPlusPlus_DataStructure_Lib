#ifndef __QLIST_H__
#define __QLIST_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QList : public QObject
{
    protected:
        struct Node : public QObject
        {
            T value;
            Node *next;
            Node *pre;
        };

        Node *m_header;
        mutable Node *m_current;
        int m_size;

    protected :
        inline int mod(int i) const { return i % this->size(); }
        inline void del(Node *pre, Node *next)
        {
            Node *toDel = pre->next;

            if (toDel == this->m_current)
            {
                this->m_current = this->m_current->pre;
            }

            pre->next = next;
            next->pre = pre;
            this->m_size--;

            delete toDel;
        }

        Node *position(int i) const
        {
            Node *ret = this->m_header;
            bool flag = i <= this->size() / 2;
            i = flag ? i : (this->size() - i + 1);

            for (int p = -1; (p < i) && ret; p++)
            {
                if (flag) ret = ret->next;
                else ret = ret->pre;
            }

            return ret;
        }

        QList(const QList<T> &obj);
        QList &operator==(const QList<T> &obj);

    public:
        QList(QObject *parent = NULL) : QObject(parent)
        {
            this->m_header = reinterpret_cast<Node *>(malloc(sizeof(Node)));
            this->m_current = this->m_header;
            this->m_size = 0;

            if (this->m_header == NULL)
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QList Note object.");
                return;
            }

            this->m_header->next = this->m_header;
            this->m_header->pre = this->m_header;
        }
        ~QList()
        {
            clear();
            if (this->m_header)
            {
                free(this->m_header);
            }
        }

        void clear()
        {
            while(this->size() > 0)
            {
                this->removeAt(0);
            }
        }

        bool contains(const T &value) const
        {
            for(this->move(0); !this->end(); this->next())
            {
                if (this->current() == value)
                {
                    return true;
                }
            }
            return false;
        }
        int count(const T &value) const
        {
            int i = 0;
            for(this->move(0); !this->end(); this->next())
            {
                if (this->current() == value)
                {
                    i++;
                }
            }
            return i;
        }
        int indexOf(const T &value, int from = 0) const
        {
            int i = from;
            for(this->move(from); !this->end(); this->next(), i++)
            {
                if (this->current() == value)
                {
                    return i;
                }
            }
            return -1;
        }
        int lastIndexOf(const T &value, int from = -1) const
        {
            from = (from == -1) ? this->size() : from;
            int i = from;
            for(this->move(from); !this->end(); this->pre(), i--)
            {
                if (this->current() == value)
                {
                    return i;
                }
            }
            return -1;
        }

        inline void move(int from, int to) {  }

        inline void move(int i) const { this->m_current = position(mod(i)); }
        inline bool end() const { return (this->m_current == this->m_header); }
        inline T &current()
        {
            if (end())
            {
                THROW_EXCEPTION(QInvalidOperationException, "No value at current position.");
            }

            return this->m_current->value;
        }
        inline const T &current() const { return const_cast< QList<T>& >(*this).current(); }
        inline void next() const { if (!end()) this->m_current = this->m_current->next; }
        inline void pre() const { if (!end()) this->m_current = this->m_current->pre; }

        inline bool beginsWith(const T &value) { return !this->empty() && (this->first() == value); }
        inline bool endsWith(const T &value) { return !this->empty() && (this->last() == value); }

        inline const T &at(int i) { return this->position(mod(i))->value; }
        inline T &first() { return this->m_header->next->value; }
        inline const T &first() const { return const_cast< QList<T>& >(*this).first(); }
        inline const T &constFirst() const { return this->first(); }
        inline T &last() { return this->m_header->pre->value; }
        inline const T &last() const { return const_cast< QList<T>& >(*this).last(); }
        inline const T &constLast() const { return this->last(); }
        inline T &front() { return this->first(); }
        inline const T &front() const { return this->first(); }
        inline const T &constFront() const { return this->front(); }
        inline T &back() { return this->last(); }
        inline const T &back() const { return this->last(); }
        inline const T &constBack() const { return this->back(); }
        inline T takeAt(int i) { return this->at(i); }
        inline T takeFirst() { return this->first(); }
        inline T takeLast() { return this->last(); }

        inline int size() const { return this->m_size; }
        inline int length() const { return this->size(); }
        inline int capacity() const { return this->size(); }
        inline int count() const { return this->size(); }
        inline bool empty() const { return (this->size() == 0); }
        inline bool isEmpty() const { return this->empty(); }

        inline bool prepend(const T &e) { return this->insert(0, e); }
        inline bool append(const T &e) { return this->insert(this->size(), e); }
        inline bool pushFront(const T &e) { return this->prepend(e); }
        inline bool pushBack(const T &e) { return this->append(e); }
        inline void popFront() { this->removeFirst(); }
        inline void popBack() { this->removeLast(); }

        inline bool insert(int i, const T &e)
        {
            Node *node = new Node();
            if (node == NULL)
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert new node.");
                return false;
            }

            Node *pre = position(i % (this->m_size + 1) - 1);
            Node *next = pre->next;

            node->value = e;
            node->next = next;
            node->pre = pre;
            pre->next = node;
            next->pre = node;

            this->m_size++;

            return true;
        }
        inline void removeAt(int i) {  Node *toDel = this->position(mod(i)); del(toDel->pre, toDel->next); }
        inline void removeFirst() { this->removeAt(0); }
        inline void removeLast() { this->removeAt(this->size() - 1); }
        inline bool removeOne(const T &value)
        {
            for (Node *pos = this->m_header->next, *n = pos->next;
                 pos != this->m_header; pos = n, n = pos->next)
            {
                if (pos->value == value)
                {
                    del(pos->pre, pos->next);
                    return true;
                }
            }
            return false;
        }
        inline int removeAll(const T &value)
        {
            int i = 0;
            for (Node *pos = this->m_header->next, *n = pos->next;
                 pos != this->m_header; pos = n, n = pos->next)
            {
                if (pos->value == value)
                {
                    del(pos->pre, pos->next);
                    i++;
                }
            }
            return i;
        }

        inline T &operator[](int i) { return position(mod(i))->value; }
        inline T operator[](int i) const { return const_cast< QList<T>& >(*this).operator[](i); }
};

}

#endif
