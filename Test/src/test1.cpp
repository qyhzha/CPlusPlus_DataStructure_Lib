#include <iostream>
#include "LinkQueue.h"

using namespace qLib;
using namespace std;

class Test : public Object
{
protected:
    int m_value;
public:
    Test() : m_value(0)
    {
        std::cout << "Test()" << std::endl;
    }

    Test(const Test& obj)
    {
        m_value = obj.m_value;
        std::cout << "Test(const Test& obj)" << std::endl;
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
        std::cout << "~Test()" << std::endl;
    }
};

int test()
{
    LinkQueue<Test> obj;

    try
    {
        for(int i = 0; i < 10; i++)
        {
            Test test;
            test.setValue(i);
            obj.enqueue(test);
        }
    }
    catch(const Exception& e)
    {
        cout << "location = " << e.location() << endl;
        cout << "message = " << e.message() << endl;
    }

    cout << "begin..." << endl;

    while(obj.length() > 0)
    {
        cout << "value = " << obj.front().value() << endl;
        obj.dequeue();
    }

    cout << "end..." << endl;

    return 0;
}
