#ifndef __QOBJECT_H__
#define __QOBJECT_H__

#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace qLib
{

class QObject
{
    protected:
        char *m_name;
        QObject *m_parent;

    public:
        inline QObject(QObject *parent = NULL) { this->m_name = strdup("object"); this->m_parent = NULL; }
        inline QObject(const QObject &obj, QObject *parent = NULL) { this->m_name = strdup(obj.m_name); this->m_parent = obj.m_parent; }
        virtual ~QObject() = 0;

        inline void *operator new (size_t size) throw() { return malloc(size); }
        inline void operator delete (void *p) { if (p) free(p); }
        inline void *operator new[](size_t size) throw() { return malloc(size); }
        inline void operator delete[](void *p) { if (p) free(p); }

        inline char *name() { return this->m_name; }
        inline const char *name() const { return this->m_name; }
        inline void setName(const char *name) { this->m_name = strdup(name); }

        inline QObject *parent() { return this->m_parent; }
        inline const QObject *parent() const { return this->m_parent; }
        inline void setParent(QObject *parent) { this->m_parent = parent; }

        inline QObject &operator=(const QObject &obj)
        {
            if (this != &obj)
            {
                if (this->m_name != NULL)
                {
                    free(this->m_name);
                }

                this->m_name = strdup(obj.m_name);
                this->m_parent = obj.m_parent;
            }
        }
};

}

#endif // OBJECT_H
