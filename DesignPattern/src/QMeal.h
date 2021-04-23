#include "QObject"
#include "QList"
#include "QSharedPointer"
#include "QItem"

class QMeal : public qLib::QObject
{
    protected :
        qLib::QList< qLib::QSharedPointer<QItem> > m_list;

    public :
        bool addItem(const qLib::QSharedPointer<QItem> item);
        float cost() const;
        void show() const;
};