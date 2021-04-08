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

    public:
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

        T &operator[](int i)
        {
            if ((i < 0) || (i >= length()))
            {
                THROW_EXCEPTION(QIndexOutOfBoundsException, "Paramer i out of bounds ...");
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

        virtual int length() const = 0;
    };

}

#endif // ARRAY_H
