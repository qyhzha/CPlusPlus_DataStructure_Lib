#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "QObject.h"

namespace qLib
{
#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class QException : public QObject
{
    protected:
        char *m_message;
        char *m_location;

    protected:
        void init(const char *message, const char *file, int line);

    public:
        QException();
        QException(const char *message);
        QException(const char *file, int line);
        QException(const char *message, const char *file, int line);
        QException(const QException &e);
        QException &operator =(const QException &e);

        virtual const char *message() const;
        virtual const char *location() const;

        virtual ~QException() = 0;
};
}

namespace qLib
{
class QArithmeticException : public QException
{
    public:
        QArithmeticException() : QException() {}
        QArithmeticException(const char *message) : QException(message) {}
        QArithmeticException(const char *file, int line) : QException(file, line) {}
        QArithmeticException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QArithmeticException(const QArithmeticException &e): QException(e) {}
        QArithmeticException &operator =(const QArithmeticException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

namespace qLib
{
class QIndexOutOfBoundsException : public QException
{
    public:
        QIndexOutOfBoundsException() : QException() {}
        QIndexOutOfBoundsException(const char *message) : QException(message) {}
        QIndexOutOfBoundsException(const char *file, int line) : QException(file, line) {}
        QIndexOutOfBoundsException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QIndexOutOfBoundsException(const QIndexOutOfBoundsException &e): QException(e) {}
        QIndexOutOfBoundsException &operator =(const QIndexOutOfBoundsException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

namespace qLib
{
class QInvalidParameterException : public QException
{
    public:
        QInvalidParameterException() : QException() {}
        QInvalidParameterException(const char *message) : QException(message) {}
        QInvalidParameterException(const char *file, int line) : QException(file, line) {}
        QInvalidParameterException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QInvalidParameterException(const QInvalidParameterException &e): QException(e) {}
        QInvalidParameterException &operator =(const QInvalidParameterException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

namespace qLib
{
class QNoEnoughMemoryException : public QException
{
    public:
        QNoEnoughMemoryException() : QException() {}
        QNoEnoughMemoryException(const char *message) : QException(message) {}
        QNoEnoughMemoryException(const char *file, int line) : QException(file, line) {}
        QNoEnoughMemoryException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QNoEnoughMemoryException(const QNoEnoughMemoryException &e): QException(e) {}
        QNoEnoughMemoryException &operator =(const QNoEnoughMemoryException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

namespace qLib
{
class QNullPointerException : public QException
{
    public:
        QNullPointerException() : QException() {}
        QNullPointerException(const char *message) : QException(message) {}
        QNullPointerException(const char *file, int line) : QException(file, line) {}
        QNullPointerException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QNullPointerException(const QNullPointerException &e): QException(e) {}
        QNullPointerException &operator =(const QNullPointerException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

namespace qLib
{
class QInvalidOperationException : public QException
{
    public:
        QInvalidOperationException() : QException() {}
        QInvalidOperationException(const char *message) : QException(message) {}
        QInvalidOperationException(const char *file, int line) : QException(file, line) {}
        QInvalidOperationException(const char *message, const char *file, int line) : QException(message, file, line) {}
        QInvalidOperationException(const QInvalidOperationException &e): QException(e) {}
        QInvalidOperationException &operator =(const QInvalidOperationException &e)
        {
            QException::operator =(e);
            return *this;
        }
};
}

#endif // EXCEPTION_H
