#include "QDebug.h"
#include "QException.h"
#include <cstdio>
#include <cstring>
#include <cstdarg>

namespace qLib
{

static const int QDEBUG_OUTPUT_MAX_LENGTH = 2048;

const char *endl = "\r\n";

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

    memcpy(this->m_buffer + this->m_length, buffer, length);
    this->m_length += length;
    this->m_buffer[this->m_length] = '\0';

    return *this;
}

QDebug &QDebug::operator<<(const QString &string)
{
    return this->operator<<(string.str());
}

void QDebug::debug(const char *format, ...)
{
    char *buffer = new char[QDEBUG_OUTPUT_MAX_LENGTH];
    if (buffer == NULL)
    {
        THROW_EXCEPTION(QNoEnoughMemoryException, "No memory to create QDebug debug buffer.");
        return;
    }

    va_list ap;

    va_start(ap, format);
    vsnprintf(buffer, QDEBUG_OUTPUT_MAX_LENGTH, format, ap);
    va_end(ap);

    debug() << buffer;

    delete []buffer;
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
