#include "QException"
#include "QDebug"
#include "QAbstractFactory"

void FactoryPatternDemo()
{
    try
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
    }catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}