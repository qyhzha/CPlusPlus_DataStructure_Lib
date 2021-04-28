#include "QObject"
#include "QPerson"
#include "QSharedPointer"
#include "QList"

namespace qLib
{

template <typename T>
class QFilter : public QObject
{
    public :
        virtual QSharedPointer< QList< T > > filter(const QList< T > &list) const = 0;
};

}