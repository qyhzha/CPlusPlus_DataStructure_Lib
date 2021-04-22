#include "QColor.h"
#include "QDebug"

void QRed::fill() const
{
    qLib::qDebug() << "this is a Red.";
}

void QGreen::fill() const
{
    qLib::qDebug() << "this is a Green.";
}

void QBlue::fill() const
{
    qLib::qDebug() << "this is a Blue.";
}