#include "QString"
#include "QException"
#include <iostream>

void QStringTest(void)
{
    try
    {
        qLib::QString str("yonghang.qin");

        str += " is good.";

        //std::cout << "str : " << str << std::endl;


    }catch(const qLib::QException &e)
    {
        std::cout << "Location: " << e.location() << std::endl;
        std::cout << "Message: " << e.message() << std::endl;
    }
}