#ifndef __TREE_H__
#define __TREE_H__

#include "QObject.h"
#include "QException.h"
#include "QTreeNode.h"
#include "QSharedPointer.h"

namespace qLib
{

template <typename T>
class QTree : public QObject
{
protected:
    QTreeNode<T>* m_root;

    QTree(const QTree<T>&);

    QTree<T>& operator =(const QTree<T>&);

public:
    QTree() {m_root = NULL;}
    virtual bool insert(QTreeNode<T>* node) = 0;
    virtual bool insert(const T& value, QTreeNode<T>* parent) = 0;
    virtual SharedPointer< QTree<T> > remove(const T& value) = 0;
    virtual SharedPointer< QTree<T> > remove(QTreeNode<T>* node) = 0;
    virtual QTreeNode<T>* find(const T& value) const = 0;
    virtual QTreeNode<T>* find(QTreeNode<T>* node) const = 0;
    virtual QTreeNode<T>* root() const = 0;
    virtual int degree() const = 0;
    virtual int count() const = 0;
    virtual int height() const = 0;
    virtual void clear() = 0;
    virtual void begin() const = 0;
    virtual bool end() const = 0;
    virtual void next() const = 0;
    virtual T current() const = 0;
};

}

#endif // TREE_H
