#include "QMeal.h"

bool QMeal::addItem(const QItem &item)
{
    return this->m_list.insert(item);
}

float QMeal::const() const
{
    
}