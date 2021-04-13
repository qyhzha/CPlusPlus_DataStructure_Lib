#include "QObject"
#include "QArray"
#include "QDebug"
#include "QException"

class Test : public qLib::QObject
{
protected:
    int m_value;
public:
    Test() : m_value(0)
    {
        static int index = 0;
        qLib::qDebug() << "Test(" << index << ")" << qLib::endl;
        index++;
    }

    Test(const Test& obj)
    {
        m_value = obj.m_value;
        qLib::qDebug() << "Test(const Test& obj)" << qLib::endl;
    }

    void setValue(int value)
    {
        m_value = value;
    }

    int value()
    {
        return m_value;
    }

    ~Test()
    {
        static int index = 0;
        qLib::qDebug() << "~Test(" << index << ")" << qLib::endl;
        index++;
    }
};

void QArrayTest(void)
{
    try
    {
        qLib::QArray<Test> array(10);

        for(int i = 0; i < array.length(); i++)
        {
            array[i].setValue(i);
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        array[7].setValue(70);

        for(int i = 0; i < array.length(); i++)
        {
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        array.resize(20);

        for(int i = 11; i < array.length(); i++)
        {
            array[i].setValue(i * 100);
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }

        for(int i = 0; i < array.length(); i++)
        {
            qLib::qDebug() << "array[" << i << "] = " << array[i].value();
        }
    }catch(const qLib::QException &e)
    {
        qLib::qDebug() << "Location: " << e.location();
        qLib::qDebug() << "Message: " << e.message();
    }

}
