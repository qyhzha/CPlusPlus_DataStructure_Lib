#include "QException"
#include "QDebug"
#include "QList"
#include "QTest.h"

void QListTest(void)
{
    try
    {
        qLib::QList<QTest> list;

        for(int i = 0; i < 10; i++)
        {
            QTest test(i);

            list.insert(test);
        }

        qLib::qDebug() << "length = " << list.length();

        for(list.move(0); !list.end(); list.next())
        {
            qLib::qDebug() << "value = " << list.current().value();
        }

        for(int i = 0; i < 5; i++)
        {
            list.remove();
        }

        for(list.move(0); !list.end(); list.next())
        {
            qLib::qDebug() << "value = " << list.current().value();
        }

        for(int i = 0; i < 10; i++)
        {
            list.remove();
        }

        for(list.move(0); !list.end(); list.next())
        {
            qLib::qDebug() << "value = " << list.current().value();
        }

        for(int i = 0; i < 5; i++)
        {
            QTest test(i * 10);

            list.insert(test);
        }

        for(list.move(0); !list.end(); list.next())
        {
            qLib::qDebug() << "value = " << list.current().value();
        }
    }catch(const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }
}