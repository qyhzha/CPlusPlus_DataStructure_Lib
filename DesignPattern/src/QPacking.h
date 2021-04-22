#include "QObject"
#include "QString"

class QPacking : public qLib::QObject
{
    public :
        virtual qLib::QString pack() const = 0;
};

class QWrapper : public QPacking
{
    public :
        qLib::QString pack() const;
};

class QBottle : public QPacking
{
    public :
        qLib::QString pack() const;
};