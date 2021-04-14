#ifndef __QBTREENODE_H__
#define __QBTREENODE_H__

#include "QTreeNode.h"

namespace qLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class QBTreeNode : public QTreeNode<T>
{
public:
    QBTreeNode<T>* m_left;
    QBTreeNode<T>* m_right;

    QBTreeNode()
    {
        m_left = NULL;
        m_right = NULL;
    }

    static QBTreeNode<T>* NewNode()
    {
        QBTreeNode<T>* ret = new QBTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    static QBTreeNode<T>* NewNode(const T& obj)
    {
        QBTreeNode<T>* ret = new QBTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
            ret->value = obj;
        }

        return ret;
    }

    static QBTreeNode<T>* NewNode(const T& obj, QTreeNode<T>* node)
    {
        QBTreeNode<T>* ret = new QBTreeNode<T>();

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

#endif
