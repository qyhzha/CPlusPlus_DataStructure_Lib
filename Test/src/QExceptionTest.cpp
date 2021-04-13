#include "QException"
#include <iostream>

void QExceptionTest(void)
{
    try
    {
        THROW_EXCEPTION(QInvalidOperationException, "QException Test");
    }
    catch(QException e)
    {
        std::cout << "location : " << e.location() << std::endl;
        std::cout << "message : " << e.message() << std::endl;
    }
}