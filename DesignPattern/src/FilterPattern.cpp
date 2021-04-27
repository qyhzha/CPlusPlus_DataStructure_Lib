#include "QObject"
#include "QString"
#include "QDebug"
#include "QException"

void FilterPatternDemo()
{
    try
    {
        /* code */
    }
    catch(const qLib::QException& e)
    {
        qLib::qDebug() << "Location : " << e.location();
        qLib::qDebug() << "Message : " << e.message();
    }
}