#include "QDebug"
#include "QException"
#include <iostream>

void QDebugTest(void)
{
    try
    {
        qLib::qDebug() << "value = " << 12;
    }catch(const qLib::QException &e)
    {
        std::cout << "Location: " << e.location() << std::endl;
        std::cout << "Message: " << e.message() << std::endl;
    }
}