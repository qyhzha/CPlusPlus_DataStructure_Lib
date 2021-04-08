#include <cstdlib>
#include <cstring>
#include "QString.h"

namespace qLib
{

QString::QString()
{
    init("");
}

QString::QString(const char *s)
{
    init(s ? s : "");
}

QString::QString(const QString &s)
{
    init(s.m_str);
}

QString::QString(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

QString::~QString()
{
    free(m_str);
}

void QString::init(const char *s)
{
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(QNullPointerException, "No enough memory to create string object...");
    }
}

bool QString::equal(const char* l, const char* r, int len) const
{
    bool ret = false;

    if(l != NULL && r != NULL)
    {
        ret = true;
        for(int i = 0; i < len; i++)
        {
            if(l[i] != r[i])
            {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

int* QString::makePmt(const char* s) const
{
    int len = strlen(s);
    int* pmt = static_cast<int*>(malloc(sizeof(int) * len));

    if(pmt)
    {
        int i = 1, ll = 0;
        pmt[0] = 0;

        while(i < len)
        {
            if(s[i] == s[ll])
            {
                i++;
                ll++;
                pmt[i] = ll;
            }
            else if(ll == 0)
            {
                i++;
                pmt[i] = 0;
            }
            else
            {
                ll = pmt[ll];
            }
        }
    }
    else
    {
        THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to find dest string...");
    }

    return pmt;
}

int QString::length() const
{
    return m_length;
}

const char* QString::str() const
{
    return m_str;
}

QString& QString::trim()
{
    int b = 0;
    int e = m_length - 1;

    while (m_str[b] == ' ') b++;
    while (m_str[e] == ' ') e--;

    if(b == 0)
    {
        m_str[e + 1] = '\0';

        m_length = e + 1;
    }
    else
    {
        for(int i = 0, j = b; j <= e; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';

        m_length = e - b + 1;
    }

    return *this;
}

QString QString::sub(int i, int len) const
{
    QString ret;

    if((i >= 0) && (i < m_length))
    {
        if(len > 0)
        {
            len = ((i + len) < m_length) ? len : m_length - i;
            char* str = static_cast<char*>(malloc(len + 1));

            strncpy(str, m_str + i, len);
            str[len] = '\0';

            ret = str;
        }
    }
    else
    {
        THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
    }

    return ret;
}

QString& QString::operator =(const QString& s)
{
    return (*this = s.m_str);
}

QString& QString::operator =(const char* s)
{
    if(m_str != s)
    {
        s = s ? s : "";

        char* str = strdup(s);

        if(str)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(s);
        }
        else
        {
            THROW_EXCEPTION(QNullPointerException, "No enough memory to copy string...");
        }
    }

    return *this;
}

QString& QString::operator =(char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

bool QString::operator ==(const QString& s) const
{
    return (strcmp(this->m_str, s.m_str) == 0);
}

bool QString::operator ==(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") == 0);
}

bool QString::operator !=(const QString& s) const
{
    return !(*this == s);
}

bool QString::operator !=(const char* s) const
{
    return !(*this == s);
}

bool QString::operator >(const QString& s) const
{
    return (strcmp(this->m_str, s.m_str) > 0);
}

bool QString::operator >(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") > 0);
}

bool QString::operator <(const QString& s) const
{
    return (strcmp(this->m_str, s.m_str) < 0);
}

bool QString::operator <(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") < 0);
}

bool QString::operator >=(const QString& s) const
{
    return (strcmp(this->m_str, s.m_str) >= 0);
}

bool QString::operator >=(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") >= 0);
}

bool QString::operator <=(const QString& s) const
{
    return (strcmp(this->m_str, s.m_str) <= 0);
}

bool QString::operator <=(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") <= 0);
}

QString QString::operator +(const QString& s) const
{
    return (*this + s.m_str);
}

QString QString::operator +(const char* s) const
{
    return QString().insert(0, s).insert(0, m_str);
}

QString& QString::operator +=(const QString& s)
{
    return *this = *this + s;
}

QString& QString::operator +=(const char* s)
{
    return *this = *this + s;
}

QString QString::operator -(const QString& s) const
{
    return (*this - s.m_str);
}

QString QString::operator -(const char* s) const
{
    return QString(*this).remove(s);
}

QString& QString::operator -=(const QString& s)
{
    return *this = *this - s;
}

QString& QString::operator -=(const char* s)
{
    return *this = *this - s;
}

char& QString::operator [](int i)
{
    if((i < 0) || (i >= m_length))
    {
        THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
    }

    return m_str[i];
}

char QString::operator [](int i) const
{
    return const_cast<QString&>(*this)[i];
}

bool QString::startWith(const QString& s) const
{
    return startWith(s.m_str);
}

bool QString::startWith(const char* s) const
{
    bool ret = s;

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool QString::endOf(const QString& s) const
{
    return endOf(s.m_str);
}

bool QString::endOf(const char* s) const
{
    bool ret = s;

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str + m_length - len, s, len);
    }

    return ret;
}

QString& QString::insert(int i, const QString &s)
{
    return insert(i, s.m_str);
}

QString& QString::insert(int i, const char* s)
{
    if((i >= 0) && (i <= m_length))
    {
        if((s != NULL) && (s[0] != '\0'))
        {
            int len = strlen(s);
            char* str = static_cast<char*>(malloc(m_length + len + 1));

            if(str)
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);

                str[m_length + len] = '\0';

                *this = str;
            }
            else
            {
                THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert string...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
    }

    return *this;
}

int QString::indexOf(const QString& s) const
{
    return indexOf(s.m_str);
}

int QString::indexOf(const char* s) const
{
    return indexOf(0, s);
}

int QString::indexOf(int start, const QString &s) const
{
    return indexOf(start, s.m_str);
}

int QString::indexOf(int start, const char* s) const
{
    int ret = -1;
    int len = strlen(s);

    if((start >= 0) && (start < m_length))
    {
        if((s != NULL) && (len > 0) && (len < m_length))
        {
            int* pmt = makePmt(s);

            if(pmt)
            {
                int i = start, j = 0;

                while((i < m_length) && (j < len))
                {
                    if(m_str[i] == s[j])
                    {
                        i++;
                        j++;
                    }
                    else if(j == 0)
                    {
                        i++;
                    }
                    else
                    {
                        j = pmt[j];
                    }
                }

                if(j == len)
                {
                    ret = i - len;
                }
            }

            free(pmt);
        }
    }
    else
    {
        THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
    }

    return ret;
}

QString& QString::remove(int i, int len)
{
    if( (i >= 0) && (i < m_length) )
    {
        int m = i;
        int n = i + len;

        while ( (m < n) && (n < m_length) )
        {
            m_str[m++] = m_str[n++];
        }

        m_str[m] = '\0';

        m_length = m;
    }
    else
    {
        THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
    }

    return *this;
}

QString& QString::remove(const QString& s)
{
    return remove(s.m_str);
}

QString& QString::remove(const char* s)
{
    return remove(indexOf(s), strlen(s));
}

QString& QString::replace(const char* t, const char* s)
{
    int index = indexOf(t);

    return remove(index, strlen(t)).insert(index, s);
}

QString& QString::replace(const char* t, const QString& s)
{
    return replace(t, s.m_str);
}

QString& QString::replace(const QString& t, const char* s)
{
    return replace(t.m_str, s);
}

QString& QString::replace(const QString& t, const QString& s)
{
    return replace(t.m_str, s.m_str);
}

}
