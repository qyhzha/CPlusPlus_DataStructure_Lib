#include "QException"
#include "QDebug"
#include "QSharedPointer"
#include "QTest.h"

void QSharedPointerTest()
{
    try
    {
        qLib::QSharedPointer<QTest> pointer1 = new QTest(10);

        qLib::qDebug() << "value: " << pointer1->value();

        pointer1->setValue(20);

        qLib::qDebug() << "value: " << pointer1->value();

        qLib::QSharedPointer<QTest> pointer2 = pointer1;

        qLib::qDebug() << "value: " << pointer2->value();

        pointer2->setValue(30);

        qLib::qDebug() << "value: " << pointer2->value();
    }catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}