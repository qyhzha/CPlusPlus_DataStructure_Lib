#include "QString"
#include "QException"
#include "QDebug"

void QStringTest(void)
{
    try
    {
        qLib::QString str("yonghang.qin");

        str += " is good.";

        qLib::qDebug() << "str : " << str << qLib::endl;

        if (str.startWith("yonghang"))
        {
            qLib::qDebug() << "str has start with yonghang." << qLib::endl;
        }
        else
        {
            qLib::qDebug() << "str don't have start with yonghang." << qLib::endl;
        }

        str.replace("good", "bad");
        str.trim();

        qLib::qDebug() << "str : " << str << qLib::endl;

        str.remove("yonghang.qin");
        str.trim();

        qLib::qDebug() << "str : " << str << qLib::endl;

        str -= "is";
        str.trim();

        qLib::qDebug() << "str : " << str << qLib::endl;

    }catch(const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location() << qLib::endl;
        qLib::qDebug() << "Message: " << e.message() << qLib::endl;
    }
}