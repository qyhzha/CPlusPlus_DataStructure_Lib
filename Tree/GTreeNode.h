#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace QinLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

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

    static GTreeNode<T>* NewNode(const T& obj, TreeNode<T>* node)
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
