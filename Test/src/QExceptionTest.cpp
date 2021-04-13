#include "QException"
#include <iostream>

using namespace qLib;

void QExceptionTest(void)
{
    try
    {
        THROW_EXCEPTION(QInvalidOperationException, "QException Test");
    }
    catch(const QException &e)
    {
        std::cout << "Location: " << e.location() << std::endl;
        std::cout << "Message: " << e.message() << std::endl;
    }
}