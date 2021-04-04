#ifndef __QOBJECT_H__
#define __QOBJECT_H__

#include <cstdio>

namespace qLib
{
class QObject
{
    protected:
        char *m_objectName;
    public:
        QObject();

        void *operator new (size_t size) throw();
        void operator delete (void *p);
        void *operator new[](size_t size) throw();
        void operator delete[](void *p);

        const char *objectName() const;
        void setObjectName(const char *name);

        virtual ~QObject() = 0;
};
}

#endif // OBJECT_H
