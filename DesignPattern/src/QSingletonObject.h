#include "QObject"

class QSingletonObject : public qLib::QObject
{
    protected :
        static QSingletonObject *m_singletonObject;

        QSingletonObject();
        QSingletonObject(const QSingletonObject &obj);

    public :
        static QSingletonObject &singletonObject();
};