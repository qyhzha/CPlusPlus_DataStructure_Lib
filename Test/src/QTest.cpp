#include "QTest.h"
#include "QDebug"

static int m_construct = 0;
static int m_destroy = 0;

QTest::QTest() : m_value(0)
{
    qLib::qDebug() << "QTest(" << m_construct << ")";
    m_construct++;
}

QTest::QTest(int i) : m_value(i)
{
    qLib::qDebug() << "QTest(" << m_construct << ")";
    m_construct++;
}

QTest::QTest(const QTest &obj) : m_value(obj.m_value)
{
    qLib::qDebug() << "QTest(" << m_construct << ")";
    m_construct++;
}

QTest::~QTest()
{
    qLib::qDebug() << "~QTest(" << m_destroy << ")";
    m_destroy++;
}

bool QTest::operator ==(const QTest &obj) const
{
    return (this->m_value == obj.m_value);
}

void QTest::setValue(int value)
{
    this->m_value = value;
}

int QTest::value() const
{
    return this->m_value;
}