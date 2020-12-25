#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cstdio>

#define qDebug(fmt, arg...) printf("[%s, %d] "fmt, ##args)

namespace QinLib
{
class Object
{
    protected:
        char *m_objectName;
    public:
        Object();

        void *operator new (size_t size) throw();
        void operator delete (void *p);
        void *operator new[](size_t size) throw();
        void operator delete[](void *p);

        const char *objectName() const;
        void setObjectName(const char *name);

        virtual ~Object() = 0;
};
}

#endif // OBJECT_H
