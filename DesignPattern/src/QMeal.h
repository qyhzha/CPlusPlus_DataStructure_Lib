#include "QObject"
#include "QList"
#include "QItem"

class QMeal : public qLib::QObject
{
    protected :
        qLib::QList<QItem> m_list;

    public :
        bool addItem(const QItem &item);
        float cost() const;
        void show() const;
};