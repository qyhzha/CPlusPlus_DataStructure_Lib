#include "QException"
#include "QDebug"
#include "QAbstractFactory"

class QFactoryProducer : public qLib::QObject
{
    public :
        QAbstractFactory *abstractFactory(const qLib::QString &string) const
        {
            if (qLib::QString::compare(string, "Color", qLib::CaseInsensitive) == 0)
            {
                return new QColorFactory();
            }
            else if (qLib::QString::compare(string, "Shape", qLib::CaseInsensitive) == 0)
            {
                return new QShapeFactory();
            }

            return NULL;
        }
};

void AbstractFactoryPatternDemo()
{
    try
    {
        QAbstractFactory *factory = QFactoryProducer().abstractFactory("Shape");
        if (factory == NULL)
        {
            qLib::qDebug() << "this is not support factory.";
            return;
        }

        QShape *shape = factory->shape("Rectangle");

        if (shape != NULL)
        {
            shape->draw();

            delete shape;
        }

        shape = factory->shape("Square");

        if (shape != NULL)
        {
            shape->draw();

            delete shape;
        }

        shape = factory->shape("Circle");

        if (shape != NULL)
        {
            shape->draw();

            delete shape;
        }

        delete factory;

        factory = QFactoryProducer().abstractFactory("Color");
        if (factory == NULL)
        {
            qLib::qDebug() << "this is not support factory.";
            return;
        }

        QColor *color = factory->color("Red");

        if (color != NULL)
        {
            color->fill();

            delete color;
        }

        color = factory->color("Green");

        if (color != NULL)
        {
            color->fill();

            delete color;
        }

        color = factory->color("Blue");

        if (color != NULL)
        {
            color->fill();

            delete color;
        }
    }
    catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}