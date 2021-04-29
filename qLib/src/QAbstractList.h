#ifndef __QABSTRACTLIST_H__
#define __QABSTRACTLIST_H__

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

        enum QDirection
        {
            QPre,
            QNext,
        };

        Node *m_header;
        mutable Node *m_current;
        int m_size;
        mutable int m_step;

    protected :
        Node *position(int i, QDirection direct = QNext) const
        {
            Node *ret = this->m_header;

            for (int p = -1; (p < i) && ret; p++)
            {
                if (direct == QNext)
                {
                    ret = ret->next;
                }
                else
                {
                    ret = ret->pre;
                }
            }

            return ret;
        }

        QList(const QList<T> &obj);
        QList &operator==(const QList<T> &obj);

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
            this->m_header->pre = NULL;
        }
        ~QList() { clear();if (this->m_header) free(this->m_header); }

        inline int size() const { return this->m_size; }
        inline int length() const { return this->size(); }
        inline int capacity() const { return this->size(); }
        inline bool isEmpty() const { return (this->size() == 0); }

        virtual bool insert(int i, const T &e) = 0;
        virtual bool remove(int i) = 0;
        virtual void clear() = 0;
        virtual bool insert(const T &e) = 0;
        virtual bool remove() = 0;

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

        T &operator[](int i)
        {
            if ((i < 0) ||(i >= this->m_size))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Index out of bound.");
            }

            return position(i)->value;
        }

        T operator[](int i) const
        {
            if ((i < 0) ||(i >= this->m_size))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Index out of bound.");
            }

            return position(i)->value;
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
                THROW_EXCEPTION(QInvalidOperationException, "No value at current position.");
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
