#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{

template <typename T>
class QArray : public QObject
{
    protected:
        T *m_array;
        int m_length;

        T *copy(T *array, int len, int newlen)
        {
            T *ret = new T[newlen];

            if (ret != NULL)
            {
                for (int i = 0; (i < len) && (i < newlen); i++)
                {
                    ret[i] = array[i];
                }
            }

            return ret;
        }

        void update(T *array, int length)
        {
            if (array != NULL)
            {
                T *temp = this->m_array;

                this->m_array = array;
                this->m_length = length;

                delete temp;
            }
        }

    public:
        QArray(int length)
        {
            m_length = 0;
            m_array = new T[length];

            if (m_array == NULL)
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QArray Object.")
                return;
            }

            m_length = length;
        }

        QArray(const QArray<T> &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        QArray &operator =(const QArray<T> &obj)
        {
            if (this != &obj)
            {
                update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
            }
        }

        ~QArray()
        {
            delete[] m_array;
        }

        int length() const
        {
            return m_length;
        }

        void resize(int length)
        {
            if (m_length != length)
            {
                update(copy(this->m_array, m_length, length), length);
            }
        }

        virtual bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < length()));

            if (ret)
            {
                m_array[i] = e;
            }

            return ret;
        }

        virtual bool get(int i, T &e) const
        {
            bool ret = ((i >= 0) && (i < length()));

            if (ret)
            {
                e = m_array[i];
            }

            return ret;
        }

        virtual T get(int i) const
        {
            if ((i < 0) || (i >= length()))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Paramer i is invalid.");
            }

            return m_array[i];
        }

        T &operator[](int i)
        {
            if ((i < 0) || (i >= length()))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Paramer i is invalid.");
            }

            return m_array[i];
        }

        T operator[](int i) const
        {
            return const_cast<QArray<T> &>(*this)[i];
        }

        T *array() const
        {
            return m_array;
        }
};

}

#endif // ARRAY_H
