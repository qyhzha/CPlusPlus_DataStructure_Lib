#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "QContainer.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QArray : public QContainer<T>
{
    protected:
        T *copy(T *array, int length)
        {
            T *ret = new T[length];

            if (ret != NULL)
            {
                for (int i = 0; i < length; i++)
                {
                    ret[i] = array[i];
                }
            }

            return ret;
        }

        void update(T *array, int length)
        {
            this->m_space = NULL;
            this->m_size = 0;

            if (array == NULL || length <= 0)
            {
                THROW_EXCEPTION(QInvalidParameterException, "Paramter is invalid.")
                return;
            }

            T *temp = this->m_space;

            this->m_space = array;
            this->m_size = length;

            delete[] temp;
        }

    public:
        QArray(int length)
        {
            this->m_size = 0;
            this->m_space = new T[length];

            if (this->m_space == NULL)
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QArray Object.")
                return;
            }

            this->m_size = length;
        }

        QArray(const QArray<T> &obj)
        {
            update(copy(obj.this->m_space, obj.this->m_size), obj.this->m_size);
        }

        QArray &operator =(const QArray<T> &obj)
        {
            if (this != &obj)
            {
                update(copy(obj.this->m_space, obj.this->m_size), obj.this->m_size);
            }
        }

        ~QArray()
        {
            delete[] this->m_space;
        }

        void resize(int length)
        {
            if (this->m_size != length)
            {
                update(copy(this->this->m_space, this->m_size, length), length);
            }
        }

        virtual bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < length()));

            if (ret)
            {
                this->m_space[i] = e;
            }

            return ret;
        }

        virtual bool get(int i, T &e) const
        {
            bool ret = ((i >= 0) && (i < length()));

            if (ret)
            {
                e = this->m_space[i];
            }

            return ret;
        }

        virtual T get(int i) const
        {
            if ((i < 0) || (i >= length()))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Paramer i is invalid.");
            }

            return this->m_space[i];
        }

        T &operator[](int i)
        {
            if ((i < 0) || (i >= length()))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Paramer i is invalid.");
            }

            return this->m_space[i];
        }

        T operator[](int i) const
        {
            return const_cast<QArray<T> &>(*this)[i];
        }

        T *array() const
        {
            return this->m_space;
        }
};

}

#endif // ARRAY_H
