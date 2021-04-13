#include "QDebug.h"
#include "QException.h"
#include <cstdio>
#include <cstring>

namespace qLib
{

QDebug::QDebug()
{
    this->m_handler = NULL;
    this->m_length = 0;
    this->m_buffer = new char[QDEBUG_OUTPUT_MAX_LENGTH];
    if (this->m_buffer == NULL)
    {
        THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QDebug message buffer.");
        return;
    }

    this->m_buffer[0] = '\0';
}

QDebug::~QDebug()
{
    output(this->m_buffer);
    delete []this->m_buffer;
}

QDebug &QDebug::operator<<(int value)
{
    char buffer[16];

    snprintf(buffer, sizeof(buffer), "%d", value);

    return this->operator<<(buffer);
}

QDebug &QDebug::operator<<(const char *buffer)
{
    int length = strlen(buffer);

    if (buffer == NULL || length + this->m_length >= QDEBUG_OUTPUT_MAX_LENGTH)
    {
        THROW_EXCEPTION(QInvalidParameterException, "Parameter is invalid.");
        return *this;
    }

    memcpy(this->m_buffer, buffer, length);
    this->m_length += length;

    return *this;
}

QDebug &QDebug::operator<<(const QString &string)
{
    return this->operator<<(string.str());
}

void QDebug::output(const char *buffer)
{
    if (m_handler != NULL)
    {
        m_handler(buffer);
    }
    else
    {
        fprintf(stderr, "%s\r\n", buffer);
        fflush(stderr);
    }
}

}