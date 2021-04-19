#ifndef __QDUALCIRCLELIST_H__
#define __QDUALCIRCLELIST_H__

#include "QDualList.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QDualCircleList : public QDualList<T>
{
    protected:
        typedef typename QDualList<T>::Node Node;

        int mod(int i) const
        {
            return (this->m_size == 0) ? 0 : (i % this->m_size);
        }

        bool insert(int i, const T &obj, bool isHeader)
        {
            bool ret = true;

            i = i % (this->m_size + 1);

            ret = QDualList<T>::insert(i, obj, isHeader);

            if (ret)
            {
                if (i == 0)
                {
                    this->m_header->next->pre = this->m_header;
                }

                if (i == this->m_size - 1)
                {
                    this->m_header->pre->next = this->m_header;
                }
            }

            return ret;
        }

        bool remove(int i, bool isHeader)
        {
            bool ret = true;

            i = mod(i);

            ret = QDualList<T>::remove(i, isHeader);

            if (ret)
            {
                if (i == 0)
                {
                    this->m_header->next->pre = this->m_header;
                }

                if (i == this->m_size - 1)
                {
                    this->m_header->pre->next = this->m_header;
                }
            }

            return ret;
        }

    public:
        QDualCircleList()
        {
            this->m_header->pre = this->m_header;
            this->m_header->next = this->m_header;
        }

        ~QDualCircleList()
        {
            clear();
        }

        bool insert(int i, const T &obj)
        {
            return insert((i <= this->m_size) ? i : (this->m_size - i), obj, (i <= this->m_size));
        }

        bool insert(const T &obj)
        {
            return insert(0, obj, false);
        }

        bool remove(int i)
        {
            return remove((i <= this->m_size) ? i : (this->m_size - i), (i <= this->m_size));
        }

        bool remove()
        {
            return remove(0, false);
        }

        bool set(int i, const T &obj)
        {
            return QDualList<T>::set(mod(i), obj);
        }

        bool get(int i, T &obj) const
        {
            return QDualList<T>::get(mod(i), obj);
        }

        T get(int i) const
        {
            return QDualList<T>::get(mod(i));
        }

        T &operator [](int i)
        {
            return QDualList<T>::operator[](mod(i));
        }

        T operator [](int i) const
        {
            return const_cast<QDualCircleList<T> &>(*this).operator[](i);
        }

        void clear()
        {
            while (this->m_size > 1)
            {
                remove(1);
            }

            remove(0);
        }

        bool move(int i, int step = 1) const
        {
            return QDualList<T>::move(mod(i), step);
        }

        bool next() const
        {
            int i = 0;
            while ((i < this->m_step) && !QDualList<T>::end())
            {
                this->m_current = this->m_current->next;

                if (this->m_current != this->m_header)
                {
                    i++;
                }
            }

            return (i == this->m_step);
        }

        bool pre() const
        {
            int i = 0;
            while ((i < this->m_step) && !QDualList<T>::end())
            {
                this->m_current = this->m_current->pre;

                if (this->m_current != this->m_header)
                {
                    i++;
                }
            }

            return (i == this->m_step);
        }
};

}

#endif
