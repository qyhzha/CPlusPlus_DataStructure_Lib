#ifndef __GTREENODE_H__
#define __GTREENODE_H__

#include "QTreeNode.h"
#include "QLinkList.h"

namespace qLib
{

template <typename T>
class GTreeNode : public QTreeNode<T>
{
public:
    QLinkList<GTreeNode<T>*> child;

    GTreeNode()
    {

    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    static GTreeNode<T>* NewNode(const T& obj)
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
            ret->value = obj;
        }

        return ret;
    }

    static GTreeNode<T>* NewNode(const T& obj, QTreeNode<T>* node)
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
            ret->value = obj;
            ret->parent = node;
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
