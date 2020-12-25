#include "Object.h"
#include <cstdlib>
#include <cstring>

namespace QinLib
{

Object::Object()
{
    m_objectName = strdup("object");
}

void* Object::operator new(size_t size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p)
{
    if(p != NULL) free(p);
}

void* Object::operator new[](size_t size) throw()
{
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    if(p != NULL) free(p);
}

const char* Object::objectName() const
{
    return m_objectName;
}

void Object::setObjectName(const char *name)
{
    if(m_objectName != NULL) free(m_objectName);
    m_objectName = strdup(name);
}

Object::~Object()
{
    if(m_objectName != NULL) free(m_objectName);
}

}

