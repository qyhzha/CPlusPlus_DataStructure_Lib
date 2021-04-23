#include "QMeal"
#include "QObject"
#include "QDebug"

class QMealBuilder : public qLib::QObject
{
    public :
        QMeal *prepareVegMeal()
        {
            QMeal *meal = new QMeal();
            if (meal == NULL)
            {
                return NULL;
            }

            meal->addItem(new QVegBurger());
            meal->addItem(new QCoke());

            return meal;
        }

        QMeal *prepareNonVegMeal()
        {
            QMeal *meal = new QMeal();
            if (meal == NULL)
            {
                return NULL;
            }

            meal->addItem(new QChickenBurger());
            meal->addItem(new QPepsi());
            return meal;
        }
};

void BuilderPatternDemo()
{
    QMealBuilder builder;

    QMeal *meal = builder.prepareVegMeal();

    if (meal != NULL)
    {
        qLib::qDebug() << "cost: " << meal->cost();
        meal->show();

        delete meal;
    }

    meal = builder.prepareNonVegMeal();

    if (meal != NULL)
    {
        qLib::qDebug() << "cost: " << meal->cost();
        meal->show();

        delete meal;
    }
}