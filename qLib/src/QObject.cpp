#include "QObject.h"
#include <cstdlib>
#include <cstring>

namespace qLib
{

QObject::QObject()
{
    m_objectName = strdup("object");
}

void *QObject::operator new (size_t size) throw()
{
    return malloc(size);
}

void QObject::operator delete (void *p)
{
    if (p != NULL)
    {
        free(p);
    }
}

void *QObject::operator new[](size_t size) throw()
{
    return malloc(size);
}

void QObject::operator delete[](void *p)
{
    if (p != NULL)
    {
        free(p);
    }
}

const char *QObject::objectName() const
{
    return m_objectName;
}

void QObject::setObjectName(const char *name)
{
    if (m_objectName != NULL)
    {
        free(m_objectName);
    }
    m_objectName = strdup(name);
}

QObject::~QObject()
{
    if (m_objectName != NULL)
    {
        free(m_objectName);
    }
}

}

