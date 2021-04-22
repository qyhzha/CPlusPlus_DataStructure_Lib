#include "QSingletonObject.h"

QSingletonObject *QSingletonObject::m_singletonObject = new QSingletonObject();

QSingletonObject::QSingletonObject()
{

}

QSingletonObject::QSingletonObject(const QSingletonObject &obj)
{

}

QSingletonObject &QSingletonObject::singletonObject()
{
    return *m_singletonObject;
}