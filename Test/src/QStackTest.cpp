#include "QException"
#include "QDebug"
#include "QStack"
#include "QTest.h"

void QStackTest()
{
    try
    {
        qLib::QStack<QTest> stack;

        while(stack.length() > 0)
        {
            QTest test = stack.pop();

            qLib::qDebug() << "value: " << test.value();
        }

        for (int i = 0; i < 10; i++)
        {
            QTest test(i);

             qLib::qDebug() << "value: " << test.value();

            stack.push(test);
        }

        qLib::qDebug() << "head: " << stack.top().value() << "; name: " << stack.top().objectName();

        qLib::qDebug() << "length: " << stack.length();

        while(stack.length() > 0)
        {
            QTest test = stack.pop();

            qLib::qDebug() << "value: " << test.value();
        }

        qLib::qDebug() << "hasData: " << !stack.isEmpty();
    }
    catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}