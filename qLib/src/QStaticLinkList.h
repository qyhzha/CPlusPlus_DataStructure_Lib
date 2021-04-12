#ifndef __STATICLINKLIST_H__
#define __STATICLINKLIST_H__

#include "QLinkList.h"
#include <cstring>

namespace qLib
{

template <typename T, int N>
class QStaticLinkList : public QLinkList<T>
{
protected:
    typedef typename QLinkList<T>::Node Node;

    struct SNode : Node
    {
        void* operator new(unsigned int size, void* address)
        {
            (void)size;
            return address;
        }
    };

    unsigned char m_space[sizeof(Node) * N];
    bool m_used[N];

    Node* create()
    {
        Node* ret = NULL;

        for(int i = 0; i < N; i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<Node*>(m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = true;
                break;
            }
        }

        return ret;
    }

    void destroy(Node *node)
    {
        Node* space = reinterpret_cast<Node*>(m_space);
        for(int i = 0; i < N; i++)
        {
            if(space == node)
            {
                m_used[i] = false;
                space->~Node();
            }
        }
    }
public:
    QStaticLinkList()
    {
        memset(m_used, false, sizeof(m_used));
    }

    int capacity()
    {
        return N;
    }
};

}

#endif // STATICLINKLIST_H
