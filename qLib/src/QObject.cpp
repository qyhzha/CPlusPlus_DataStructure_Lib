#include "QObject.h"

namespace qLib
{

QObject::~QObject()
{
    if (this->m_name != NULL)
    {
        free(this->m_name);
    }
}

}

