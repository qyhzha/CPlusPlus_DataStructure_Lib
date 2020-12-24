#include <iostream>
#include "ListGraph.h"
#include "Exception.h"

using namespace QinLib;

class Test : public Object
{
    protected:
        int m_value;
    public:
        Test() : m_value(0)
        {
            std::cout << "Test()" << std::endl;
        }

        Test(int value) : m_value(value)
        {
            std::cout << "Test()" << std::endl;
        }

        Test(const Test &obj)
        {
            m_value = obj.m_value;
            std::cout << "Test(const Test& obj)" << std::endl;
        }

        bool operator ==(const Test &obj) const
        {
            return (m_value == obj.m_value);
        }

        bool operator ==(int value) const
        {
            return (m_value == value);
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


int main()
{
    try
    {
        ListGraph<int, int> mtg;

        for (int i = 0; i < 10; i++)
        {
            mtg.addVertex(i);
        }

        for (int i = 0; i < mtg.vCount(); i++)
        {
            std::cout << mtg.getVertex(i) << std::endl;
        }
    }
    catch (const Exception &e)
    {
        std::cout << "Location: " << e.location() << std::endl;
        std::cout << "Message: " << e.message() << std::endl;
    }

    return 0;
}
