#include "QException"
#include "QDebug"
#include "QCircleList"
#include "QTest.h"

void QCircleListTest()
{
    try
    {
        qLib::QCircleList<QTest> list;

        for(int i = 0; i < 10; i++)
        {
            QTest test(i);

            list.insert(test);
        }

        qLib::qDebug() << "length = " << list.length();

        for(int i = 0; i < 15; i++)
        {
            qLib::qDebug() << "value = " << list.get(i).value();
        }

        for(int i = 0; i < 5; i++)
        {
            list.remove();
        }

        for(int i = 0; i < 15; i++)
        {
            qLib::qDebug() << "value = " << list.get(i).value();
        }

        for(int i = 0; i < 10; i++)
        {
            list.remove();
        }

#if 0
        for(int i = 0; i < 15; i++)
        {
            qLib::qDebug() << "value = " << list.get(i).value();
        }
#endif

        for(int i = 0; i < 5; i++)
        {
            QTest test(i * 10);

            list.insert(test);
        }

        for(int i = 0; i < 15; i++)
        {
            qLib::qDebug() << "value = " << list.get(i).value();
        }
    }catch(const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}
