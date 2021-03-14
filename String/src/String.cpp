#include "QinLibString.h"
#include <iostream>

namespace QinLib
{

String::String()
{
    init("");
}

String::String(const char *s)
{
    init(s ? s : "");
}

String::String(const String &s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

String::~String()
{
    free(m_str);
}

void String::init(const char *s)
{
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NullPointerException, "No enough memory to create string object...");
    }
}

bool String::equal(const char* l, const char* r, int len) const
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

int* String::makePmt(const char* s) const
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
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to find dest string...");
    }

    return pmt;
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

String& String::trim()
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

String String::sub(int i, int len) const
{
    String ret;

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
        THROW_EXCEPTION(InvalidParameterException, "Paramer i is invalid...");
    }

    return ret;
}

String& String::operator =(const String& s)
{
    return (*this = s.m_str);
}

String& String::operator =(const char* s)
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
            THROW_EXCEPTION(NullPointerException, "No enough memory to copy string...");
        }
    }

    return *this;
}

String& String::operator =(char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

bool String::operator ==(const String& s) const
{
    return (strcmp(this->m_str, s.m_str) == 0);
}

bool String::operator ==(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") == 0);
}

bool String::operator !=(const String& s) const
{
    return !(*this == s);
}

bool String::operator !=(const char* s) const
{
    return !(*this == s);
}

bool String::operator >(const String& s) const
{
    return (strcmp(this->m_str, s.m_str) > 0);
}

bool String::operator >(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") > 0);
}

bool String::operator <(const String& s) const
{
    return (strcmp(this->m_str, s.m_str) < 0);
}

bool String::operator <(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") < 0);
}

bool String::operator >=(const String& s) const
{
    return (strcmp(this->m_str, s.m_str) >= 0);
}

bool String::operator >=(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") >= 0);
}

bool String::operator <=(const String& s) const
{
    return (strcmp(this->m_str, s.m_str) <= 0);
}

bool String::operator <=(const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") <= 0);
}

String String::operator +(const String& s) const
{
    return (*this + s.m_str);
}

String String::operator +(const char* s) const
{
    return String().insert(0, s).insert(0, m_str);
}

String& String::operator +=(const String& s)
{
    return *this = *this + s;
}

String& String::operator +=(const char* s)
{
    return *this = *this + s;
}

String String::operator -(const String& s) const
{
    return (*this - s.m_str);
}

String String::operator -(const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -=(const String& s)
{
    return *this = *this - s;
}

String& String::operator -=(const char* s)
{
    return *this = *this - s;
}

char& String::operator [](int i)
{
    if((i < 0) || (i >= m_length))
    {
        THROW_EXCEPTION(InvalidParameterException, "Paramer i is invalid...");
    }

    return m_str[i];
}

char String::operator [](int i) const
{
    return const_cast<String&>(*this)[i];
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::startWith(const char* s) const
{
    bool ret = s;

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = s;

    if(ret)
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str + m_length - len, s, len);
    }

    return ret;
}

String& String::insert(int i, const String &s)
{
    return insert(i, s.m_str);
}

String& String::insert(int i, const char* s)
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
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert string...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Paramer i is invalid...");
    }

    return *this;
}

int String::indexOf(const String& s) const
{
    return indexOf(s.m_str);
}

int String::indexOf(const char* s) const
{
    return indexOf(0, s);
}

int String::indexOf(int start, const String &s) const
{
    return indexOf(start, s.m_str);
}

int String::indexOf(int start, const char* s) const
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
        THROW_EXCEPTION(InvalidParameterException, "Paramer i is invalid...");
    }

    return ret;
}

String& String::remove(int i, int len)
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
        THROW_EXCEPTION(InvalidParameterException, "Paramer i is invalid...");
    }

    return *this;
}

String& String::remove(const String& s)
{
    return remove(s.m_str);
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), strlen(s));
}

String& String::replace(const char* t, const char* s)
{
    int index = indexOf(t);

    return remove(index, strlen(t)).insert(index, s);
}

String& String::replace(const char* t, const String& s)
{
    return replace(t, s.m_str);
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

}
