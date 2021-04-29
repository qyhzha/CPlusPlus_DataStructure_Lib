#include "QException"
#include "QDebug"
#include "QQueue"
#include "QTest.h"

void QQueueTest(void)
{
    try
    {
        qLib::QQueue<QTest> queue;

        while(queue.length() > 0)
        {
            QTest test = queue.dequeue();

            qLib::qDebug() << "value: " << test.value();
        }

        for (int i = 0; i < 10; i++)
        {
            QTest test(i);

             qLib::qDebug() << "value: " << test.value();

            queue.enqueue(test);
        }

        qLib::qDebug() << "head: " << queue.head().value() << "; name: " << queue.head().name();

        qLib::qDebug() << "length: " << queue.length();

        while(queue.length() > 0)
        {
            QTest test = queue.dequeue();

            qLib::qDebug() << "value: " << test.value();
        }

        qLib::qDebug() << "hasData: " << !queue.isEmpty();
    }
    catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}
