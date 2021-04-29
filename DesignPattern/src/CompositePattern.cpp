#include "QObject"
#include "QString"
#include "QList"
#include "QSharedPointer"
#include "QDebug"
#include "QException"

class QEmployeee : qLib::QObject
{
    protected :
        qLib::QString m_name;
        qLib::QString m_dept;
        int m_salary;
        qLib::QSharedPointer< qLib::QList< QEmployeee* > > m_subordinates;

    public :
        inline QEmployeee(const qLib::QString &name, const qLib::QString &dept, int salary)
        {
            this->m_name = name;
            this->m_dept = dept;
            this->m_salary = salary;
            this->m_subordinates = new qLib::QList< QEmployeee* >();
            if (this->m_subordinates == NULL)
            {
                THROW_EXCEPTION(qLib::QNoEnoughMemoryException, "No memory to create QEmployee list.");
                return;
            }
        }

        inline const qLib::QString &name() const
        {
            return this->m_name;
        }

        inline const qLib::QString &dept() const
        {
            return this->m_dept;
        }

        inline int salary() const
        {
            return this->m_salary;
        }

        inline const qLib::QSharedPointer< qLib::QList< QEmployeee* > > &subordinates() const
        {
            return this->m_subordinates;
        }

        inline bool insert(QEmployeee * const &obj)
        {
            return this->m_subordinates->insert(obj);
        }

        inline bool remove(QEmployeee * const &obj)
        {
            return this->m_subordinates->removeOne(obj);
        }
};

void CompositePatternDemo()
{

}