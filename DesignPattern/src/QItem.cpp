#include "QItem.h"

QPacking *QBurger::packing() const
{
    return new QWrapper();
}

QPacking *QColdDrink::packing() const
{
    return new QBottle();
}

qLib::QString QVegBurger::name() const
{
    return qLib::QString("VegBurger");
}

float QVegBurger::price() const
{
    return 11.5;
}

qLib::QString QChickenBurger::name() const
{
    return qLib::QString("ChickenBurger");
}

float QChickenBurger::price() const
{
    return 15.5;
}

qLib::QString QCoke::name() const
{
    return qLib::QString("Coke");
}

float QCoke::price() const
{
    return 2.5;
}

qLib::QString QPepsi::name() const
{
    return qLib::QString("Pepsi");
}

float QPepsi::price() const
{
    return 2.5;
}