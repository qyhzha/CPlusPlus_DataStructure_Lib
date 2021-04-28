#include "QString.h"

namespace qLib
{

class QPerson : public QObject
{
    protected :
        QString m_name;
        QString m_gender;
        QString m_maritalStatus;

    public :
        inline QPerson(const QString &name, const QString &gender, const QString &maritalStatus)
        {
            this->m_name = name;
            this->m_gender = gender;
            this->m_maritalStatus = maritalStatus;
        }

        inline QPerson(const QPerson &obj)
        {
            this->m_name = obj.m_name;
            this->m_gender = obj.m_gender;
            this->m_maritalStatus = obj.m_maritalStatus;
        }

        inline QString name() { return this->m_name; }
        inline QString gender() { return this->m_gender; }
        inline QString maritalStatus() { return this->m_maritalStatus; }

        inline QPerson &operator=(const QPerson &obj)
        {
            if (this != &obj)
            {
                this->m_name = obj.m_name;
                this->m_gender = obj.m_gender;
                this->m_maritalStatus = obj.m_maritalStatus;
            }

            return *this;
        }
};

}