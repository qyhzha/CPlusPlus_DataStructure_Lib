#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace QinLib
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);

    TreeNode<T>& operator =(const TreeNode<T>&);


    void* operator new(size_t size) throw()
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        parent = NULL;
        this->m_flag = false;
    }

    bool flag()
    {
        return m_flag;;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
