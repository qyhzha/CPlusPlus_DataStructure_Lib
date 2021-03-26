#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace QinLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* m_left;
    BTreeNode<T>* m_right;

    BTreeNode()
    {
        m_left = NULL;
        m_right = NULL;
    }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    static BTreeNode<T>* NewNode(const T& obj)
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
            ret->value = obj;
        }

        return ret;
    }

    static BTreeNode<T>* NewNode(const T& obj, TreeNode<T>* node)
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

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

#endif // BTREENODE_H
