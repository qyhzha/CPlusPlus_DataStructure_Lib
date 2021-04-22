#include "QObject"
#include "QString"
#include "QShape"
#include "QColor"

class QAbstractFactory : public qLib::QObject
{
    public :
        virtual QShape *shape(const qLib::QString &string) const;
        virtual QColor *color(const qLib::QString &string) const;
};

class QShapeFactory : public QAbstractFactory
{
    public :
        QShape *shape(const qLib::QString &string) const;
};

class QColorFactory : public QAbstractFactory
{
    public :
        QColor *color(const qLib::QString &string) const;
};