#include "QShape.h"
#include "QDebug"

void QRectangle::draw() const
{
    qLib::qDebug() << "this is a Rectangle.";
}

void QSquare::draw() const
{
    qLib::qDebug() << "this is a Square";
}

void QCircle::draw() const
{
    qLib::qDebug() << "this is a Circle";
}