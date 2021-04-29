#include "QObject"
#include "QString"
#include "QPerson"
#include "QSharedPointer"
#include "QList"
#include "QDebug"
#include "QException"

class QGenderFilter : public qLib::QObject
{
    public :
        qLib::QSharedPointer< qLib::QList< qLib::QPerson * > > filter(const qLib::QList< qLib::QPerson * > &list, const qLib::QString &pattern) const
        {
            qLib::QList< qLib::QPerson* > *ret = new qLib::QList< qLib::QPerson* >();

            for(list.move(0); !list.end(); list.next())
            {
                if (list.current()->gender() == pattern)
                {
                    ret->append(list.current());
                }
            }

            return ret;
        }
};

class QMaritalStatusFilter : public qLib::QObject
{
    public :
        qLib::QSharedPointer< qLib::QList< qLib::QPerson * > > filter(const qLib::QList< qLib::QPerson * > &list, const qLib::QString &pattern) const
        {
            qLib::QList< qLib::QPerson * > *ret = new qLib::QList< qLib::QPerson * >();

            for(list.move(0); !list.end(); list.next())
            {
                if (list.current()->maritalStatus() == pattern)
                {
                    ret->append(list.current());
                }
            }

            return ret;
        }
};

class QGenderAndMaritalStatusFiler : public qLib::QObject
{
    protected :
        QGenderFilter m_genderFilter;
        QMaritalStatusFilter m_maritalStatusFilter;

    public :
        qLib::QSharedPointer< qLib::QList< qLib::QPerson * > > filter(const qLib::QList< qLib::QPerson* > &list) const
        {
            return m_maritalStatusFilter.filter(*m_genderFilter.filter(list, "Male"), "Single");
        }
};

void FilterPatternDemo()
{
    try
    {
        qLib::QList< qLib::QPerson * > persons;

        persons.append(new qLib::QPerson("Robert", "Male", "Single"));
        persons.append(new qLib::QPerson("John","Male", "Married"));
        persons.append(new qLib::QPerson("Laura","Female", "Married"));
        persons.append(new qLib::QPerson("Diana","Female", "Single"));
        persons.append(new qLib::QPerson("Mike","Male", "Single"));
        persons.append(new qLib::QPerson("Bobby","Male", "Single"));

        QGenderAndMaritalStatusFiler maritalStatusFilter;

        qLib::QSharedPointer< qLib::QList< qLib::QPerson * > > filteredList = maritalStatusFilter.filter(persons);

        for(filteredList->move(0); !filteredList->end(); filteredList->next())
        {
            qLib::QPerson *person = filteredList->current();
            qLib::qDebug() << "name : " << person->name();
            qLib::qDebug() << "gender : " << person->gender();
            qLib::qDebug() << "marital status : " << person->maritalStatus();
            delete person;
        }
    }
    catch (const qLib::QException &e)
    {
        qLib::qDebug() << "Location : " << e.location();
        qLib::qDebug() << "Message : " << e.message();
    }
}
