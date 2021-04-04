#ifndef __QSTRING_H__
#define __QSTRING_H__

#include "QObject.h"
#include "QException.h"

namespace qLib
{

class QString : public QObject
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
    int* makePmt(const char* s) const;

public:
    QString();
    QString(const char* s);
    QString(const QString& s);
    QString(char c);

    int length() const;
    const char* str() const;
    QString& trim();
    QString sub(int i, int len) const;

    QString& operator =(const QString& s);
    QString& operator =(const char* s);
    QString& operator =(char c);

    bool operator ==(const QString& s) const;
    bool operator ==(const char* s) const;
    bool operator !=(const QString& s) const;
    bool operator !=(const char* s) const;
    bool operator >(const QString& s) const;
    bool operator >(const char* s) const;
    bool operator <(const QString& s) const;
    bool operator <(const char* s) const;
    bool operator >=(const QString& s) const;
    bool operator >=(const char* s) const;
    bool operator <=(const QString& s) const;
    bool operator <=(const char* s) const;

    QString operator +(const QString& s) const;
    QString operator +(const char* s) const;
    QString& operator +=(const QString& s);
    QString& operator +=(const char* s);

    QString operator -(const QString& s) const;
    QString operator -(const char* s) const;
    QString& operator -=(const QString& s);
    QString& operator -=(const char* s);

    char& operator [](int i);
    char operator [](int i) const;

    bool startWith(const QString& s) const;
    bool startWith(const char* s) const;
    bool endOf(const QString& s) const;
    bool endOf(const char* s) const;

    QString& insert(int i, const QString& s);
    QString& insert(int i, const char* s);

    int indexOf(const QString& s) const;
    int indexOf(const char* s) const;
    int indexOf(int start, const QString& s) const;
    int indexOf(int start, const char* s) const;

    QString& remove(int i, int len);
    QString& remove(const QString& s);
    QString& remove(const char* s);

    QString& replace(const char* t, const char* s);
    QString& replace(const char* t, const QString& s);
    QString& replace(const QString& t, const char* s);
    QString& replace(const QString& t, const QString& s);

    ~QString();
};

}

#endif // STRING_H
