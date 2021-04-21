#include "QException"
#include "QDebug"
#include "QString"
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

class QShapeFactory : public qLib::QObject
{
    public :
        QShape *shape(const qLib::QString &string) const
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
};

void FactoryPatternDemo()
{
    QShape *shape = QShapeFactory().shape("Rectangle");

    if (shape != NULL)
    {
        shape->draw();

        delete shape;
    }

    shape = QShapeFactory().shape("Square");

    if (shape != NULL)
    {
        shape->draw();

        delete shape;
    }

    shape = QShapeFactory().shape("Circle");

    if (shape != NULL)
    {
        shape->draw();

        delete shape;
    }

    shape = QShapeFactory().shape("Null");

    if (shape != NULL)
    {
        shape->draw();

        delete shape;
    }
}