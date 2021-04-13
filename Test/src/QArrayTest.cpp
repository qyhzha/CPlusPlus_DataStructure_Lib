#include "QArray"
#include "QDebug"
#include "QException"
#include "QTest.h"

void QArrayTest()
{
    try
    {
        qLib::QArray<QTest> array(10);

        for(int i = 0; i < array.length(); i++)
        {
            array[i].setValue(i);
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        array[7].setValue(70);

        for(int i = 0; i < array.length(); i++)
        {
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        array.resize(20);

        for(int i = 11; i < array.length(); i++)
        {
            array[i].setValue(i * 100);
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        for(int i = 0; i < array.length(); i++)
        {
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }
    }catch(const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}
