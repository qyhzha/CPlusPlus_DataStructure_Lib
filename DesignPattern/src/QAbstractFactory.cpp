#include "QAbstractFactory.h"

QShape *QAbstractFactory::shape(const qLib::QString &string) const
{
    return NULL;
}

QColor *QAbstractFactory::color(const qLib::QString &string) const
{
    return NULL;
}

QShape *QShapeFactory::shape(const qLib::QString &string) const
{
    if (qLib::QString::compare(string, "Rectangle", qLib::CaseInsensitive) == 0)
    {
        return new QRectangle();
    }
    else if (qLib::QString::compare(string, "Square", qLib::CaseInsensitive) == 0)
    {
        return new QSquare();
    }
    else if (qLib::QString::compare(string, "Circle", qLib::CaseInsensitive) == 0)
    {
        return new QCircle();
    }

    return NULL;
}

QColor *QColorFactory::color(const qLib::QString &string) const
{
    if (qLib::QString::compare(string, "Red", qLib::CaseInsensitive) == 0)
    {
        return new QRed();
    }
    else if (qLib::QString::compare(string, "Blue", qLib::CaseInsensitive) == 0)
    {
        return new QBlue();
    }
    else if (qLib::QString::compare(string, "Green", qLib::CaseInsensitive) == 0)
    {
        return new QGreen();
    }

    return NULL;
}