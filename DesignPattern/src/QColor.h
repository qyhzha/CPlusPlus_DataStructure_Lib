#include "QObject"
#include "QString"

class QColor : public qLib::QObject
{
    public :
        virtual void fill() const = 0;
};

class QRed : public QColor
{
    public :
        void fill() const;
};

class QGreen : public QColor
{
    public :
        void fill() const;
};

class QBlue : public QColor
{
    public :
        void fill() const;
};