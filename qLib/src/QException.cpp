#include "QException.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace qLib
{

void QException::init(const char *message, const char *file, int line)
{
    if (message != NULL)
    {
        m_message = strdup(message);
    }
    else
    {
        m_message = NULL;
    }

    if (file != NULL)
    {
        char sl[16] = {0};

        int slLen = snprintf(sl, sizeof(sl), "%d", line);

        m_location = static_cast<char *>(malloc(strlen(message) + slLen + 2));

        if (m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

QException::QException()
{
    init(NULL, NULL, 0);
}

QException::QException(const char *message)
{
    init(message, NULL, 0);
}

QException::QException(const char *file, int line)
{
    init(NULL, file, line);
}

QException::QException(const char *message, const char *file, int line)
{
    init(message, file, line);
}

QException::QException(const QException &e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

QException &QException::operator =(const QException &e)
{
    if (this != &e)
    {
        if (m_message) free(m_message);
        if (m_location) free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char *QException::message() const
{
    return m_message;
}

const char *QException::location() const
{
    return m_location;
}

QException::~QException()
{
    if (m_message) free(m_message);
    if (m_location) free(m_location);
}

}
