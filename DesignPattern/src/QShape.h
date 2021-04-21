#include "QDebug"
#include "QObject"

class QShape : public qLib::QObject
{
    public :
        virtual void draw() const = 0;
};

class QRectangle : public QShape
{
    public :
        void draw() const
        {
            qLib::qDebug() << "this is a Rectangle.";
        }
};

class QSquare : public QShape
{
    public :
        void draw() const
        {
            qLib::qDebug() << "this is a Square";
        }
};

class QCircle : public QShape
{
    public :
        void draw() const
        {
            qLib::qDebug() << "this is a Circle";
        }
};