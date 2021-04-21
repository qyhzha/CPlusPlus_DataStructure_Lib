#include "QException"
#include "QDebug"
#include "QSmartPointer"
#include "QTest.h"

void QSmartPointerTest()
{
    try
    {
        qLib::QSmartPointer<QTest> pointer1 = new QTest(10);

        qLib::qDebug() << "value: " << pointer1->value();

        pointer1->setValue(20);

        qLib::qDebug() << "value: " << pointer1->value();

        qLib::QSmartPointer<QTest> pointer2 = pointer1;

        qLib::qDebug() << "value: " << pointer2->value();

        pointer2->setValue(30);

        qLib::qDebug() << "value: " << pointer2->value();
    }catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}