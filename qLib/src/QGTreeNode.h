#ifndef __QGTREENODE_H__
#define __QGTREENODE_H__

#include "QTreeNode.h"
#include "QList.h"

namespace qLib
{

template <typename T>
class QGTreeNode : public QTreeNode<T>
{
public:
    QList<QGTreeNode<T>*> child;

    QGTreeNode()
    {

    }

    static QGTreeNode<T>* NewNode()
    {
        QGTreeNode<T>* ret = new QGTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

    static QGTreeNode<T>* NewNode(const T& obj)
    {
        QGTreeNode<T>* ret = new QGTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
            ret->value = obj;
        }

        return ret;
    }

    static QGTreeNode<T>* NewNode(const T& obj, QTreeNode<T>* node)
    {
        QGTreeNode<T>* ret = new QGTreeNode<T>();

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
