#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "QObject.h"

namespace qLib
{

template <typename T>
class QTreeNode : public QObject
{
protected:
    bool m_flag;

    QTreeNode(const QTreeNode<T>&);

    QTreeNode<T>& operator =(const QTreeNode<T>&);


    void* operator new(size_t size) throw()
    {
        return QObject::operator new(size);
    }

public:
    T value;
    QTreeNode<T>* parent;

    QTreeNode()
    {
        parent = NULL;
        this->m_flag = false;
    }

    bool flag()
    {
        return m_flag;;
    }

    virtual ~QTreeNode() = 0;
};

template <typename T>
QTreeNode<T>::~QTreeNode()
{

}

}

#endif // TREENODE_H
