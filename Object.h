#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

#define deBug() std::cout << "File: " << __FILE__ << std::endl << "Line: " << __LINE__ << std::endl

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
