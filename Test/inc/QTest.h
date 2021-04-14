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

    void setValue(int value);

    int value() const;
};

#endif
