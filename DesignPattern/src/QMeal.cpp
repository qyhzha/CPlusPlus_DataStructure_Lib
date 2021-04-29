#include "QMeal.h"
#include "QDebug"

bool QMeal::addItem(const qLib::QSharedPointer<QItem> item)
{
    return this->m_list.append(item);
}

float QMeal::cost() const
{
    float ret = 0;

    for(this->m_list.move(0); !this->m_list.end(); this->m_list.next())
    {
        ret += this->m_list.current()->price();
    }

    return ret;
}

void QMeal::show() const
{
    for(this->m_list.move(0); !this->m_list.end(); this->m_list.next())
    {
        qLib::qDebug() << "current item: " << this->m_list.current()->name();
        qLib::qDebug() << "price: " << this->m_list.current()->price();
    }
}
