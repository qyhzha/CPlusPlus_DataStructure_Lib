#ifndef __QSIZE_H__
#define __QSIZE_H__

#include "QObject.h"

namespace qLib
{

class QSize : public QObject
{
    protected :
        int m_width;
        int m_height;

    public :
        inline QSize()
        {
            this->m_height = 0;
            this->m_width = 0;
        }

        inline QSize(int width, int height)
        {
            this->m_height = height;
            this->m_width = width;
        }

        inline int width() const
        {
            return this->m_width;
        }

        inline int height() const
        {
            return this->m_height;
        }

        inline int &rwidth()
        {
            return this->m_width;
        }

        inline int &rheight()
        {
            return this->m_height;
        }

        inline void setWidth(int width)
        {
            this->m_width = width;
        }

        inline void setHeight(int height)
        {
            this->m_height = height;
        }

        inline QSize &operator+=(const QSize &size)
        {
            this->m_width += size.m_width;
            this->m_height += size.m_height;

            return *this;
        }

        inline QSize &operator-=(const QSize &size)
        {
            this->m_width -= size.m_width;
            this->m_height -= size.m_height;

            return *this;
        }

        inline QSize &operator*=(const QSize &size)
        {
            this->m_width *= size.m_width;
            this->m_height *= size.m_height;

            return *this;
        }

        inline QSize &operator/=(const QSize &size)
        {
            this->m_width /= size.m_width;
            this->m_height /= size.m_height;

            return *this;
        }
};

inline const QSize operator+(const QSize &obj1, const QSize &obj2)
{
    QSize ret;

    ret.rwidth() = obj1.width() + obj2.width();
    ret.rheight() = obj1.height() + obj2.height();

    return ret;
}

inline QSize &operator-(const QSize &obj1, const QSize &obj2)
{
    QSize ret;

    ret.rwidth() = obj1.width() - obj2.width();
    ret.rheight() = obj1.height() - obj2.height();

    return ret;
}

inline QSize &operator*(const QSize &obj1, const QSize &obj2)
{
    QSize ret;

    ret.rwidth() = obj1.width() * obj2.width();
    ret.rheight() = obj1.height() * obj2.height();

    return ret;
}

inline QSize &operator/(const QSize &obj1, const QSize &obj2)
{
    QSize ret;

    ret.rwidth() = obj1.width() / obj2.width();
    ret.rheight() = obj1.height() / obj2.height();

    return ret;
}

}

#endif