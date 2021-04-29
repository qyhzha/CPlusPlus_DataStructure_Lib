#include "QSingletonObject"
#include "QDebug"

void SingletonPatternDemo()
{
    //QSingletonObject singletonObject;

    QSingletonObject &singletonObject1 = QSingletonObject::singletonObject();

    qLib::qDebug() << "object name: " << singletonObject1.name();

    singletonObject1.setName("singleton object");

    qLib::qDebug() << "object name: " << singletonObject1.name();

    QSingletonObject &singletonObject2 = QSingletonObject::singletonObject();

    qLib::qDebug() << "object name: " << singletonObject1.name();
}
