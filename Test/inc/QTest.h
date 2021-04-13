#ifndef __QTEST_H__
#define __QTEST_H__

#include "QObject"

class QTest : public qLib::QObject
{
protected:
    int m_value;

public:
    QTest();
    QTest(int i);
    QTest(const QTest& obj);
    ~QTest();

    bool operator ==(const QTest &obj) const;

    inline void setValue(int value)
    {
        m_value = value;
    }

    inline int value()
    {
        return m_value;
    }
};

#endif
