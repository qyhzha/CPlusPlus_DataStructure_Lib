#include "QSingletonObject"
#include "QDebug"

void SingletonPatternDemo()
{
    //QSingletonObject singletonObject;

    QSingletonObject &singletonObject1 = QSingletonObject::singletonObject();

    qLib::qDebug() << "object name: " << singletonObject1.objectName();

    singletonObject1.setObjectName("singleton object");

    qLib::qDebug() << "object name: " << singletonObject1.objectName();

    QSingletonObject &singletonObject2 = QSingletonObject::singletonObject();

    qLib::qDebug() << "object name: " << singletonObject1.objectName();
}