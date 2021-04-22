#include "QObject"
#include "QString"

class QShape : public qLib::QObject
{
    public :
        virtual void draw() const = 0;
};

class QRectangle : public QShape
{
    public :
        void draw() const;
};

class QSquare : public QShape
{
    public :
        void draw() const;
};

class QCircle : public QShape
{
    public :
        void draw() const;
};