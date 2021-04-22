#include "QObject"
#include "QPacking"

class QItem : public qLib::QObject
{
    public :
        virtual qLib::QString name() const = 0;
        virtual QPacking *packing() const = 0;
        virtual float price() const = 0;
};

class QBurger : public QItem
{
    public :
        QPacking *packing() const;
};

class QColdDrink : public QItem
{
    public :
        QPacking *packing() const;
};

class QVegBurger : public QBurger
{
    public :
        qLib::QString name() const;
        float price() const;
};

class QChickenBurger : public QBurger
{
    public :
        qLib::QString name() const;
        float price() const;
};

class QCoke : public QColdDrink
{
    public :
        qLib::QString name() const;
        float price() const;
};

class QPepsi : public QColdDrink
{
    public :
        qLib::QString name() const;
        float price() const;
};