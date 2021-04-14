#ifndef __QBTREE_H__
#define __QBTREE_H__

#include "QTree.h"
#include "QBTreeNode.h"
#include "QLinkQueue.h"
#include "QList.h"
#include "QSharedPointer.h"

namespace qLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template <typename T>
class QBTree : QTree<T>
{
protected:
    QLinkQueue<QBTreeNode<T>*> m_queue;

    virtual QBTreeNode<T>* find(QBTreeNode<T>* root, const T& value) const
    {
        QBTreeNode<T>* ret = NULL;

        if(root != NULL)
        {
            if(root->value == value)
            {
                ret = root;
            }
            else
            {
                ret = find(root->m_left, value);

                if(ret== NULL)
                {
                    ret = find(root->m_right, value);
                }
            }
        }

        return ret;
    }

    virtual QBTreeNode<T>* find(QBTreeNode<T>* root, QBTreeNode<T>* node) const
    {
        QBTreeNode<T>* ret = NULL;

        if(root && node)
        {
            if(root == node)
            {
                ret = root;
            }
            else
            {
                ret = find(root->m_left, node);

                if(ret== NULL)
                {
                    ret = find(root->m_right, node);
                }
            }
        }

        return ret;
    }

    virtual bool insert(QBTreeNode<T>* node, QBTreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;

        if(node)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else if(parent != NULL)
            {
                if(((pos == ANY) || (pos == LEFT)) && (parent->m_left == NULL))
                {
                    parent->m_left = node;
                }
                else if(((pos == ANY) || (pos == RIGHT)) && (parent->m_right == NULL))
                {
                    parent->m_right = node;
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = false;
                THROW_EXCEPTION(QInvalidParameterException, "Paramer tree node hava a invalid parent tree node...");
            }
        }
        else
        {
            ret = false;
            THROW_EXCEPTION(QInvalidParameterException, "Invalid paramer tree node...");
        }

        return ret;
    }

    virtual void clear(QBTreeNode<T>* node)
    {
        if(node)
        {
            clear(node->m_left);
            clear(node->m_right);

            if(node->flag())
            {
                delete node;
            }
        }
    }

    virtual void remove(QBTreeNode<T>* node, QBTree<T>*& ret)
    {
        ret = new QBTree<T>();

        if(ret)
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                QBTreeNode<T>* parent = dynamic_cast<QBTreeNode<T>*>(node->parent);

                if(parent)
                {
                    if(parent->m_left == node)
                    {
                        parent->m_left = NULL;
                    }
                    else if(parent->m_right == node)
                    {
                        parent->m_right = NULL;
                    }

                    node->parent = NULL;
                }
                else
                {
                    THROW_EXCEPTION(QInvalidParameterException, "Paramer tree node have a invalid parent tree node...");
                }
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to create new tree...");
        }
    }

    int count(QBTreeNode<T>* node) const
    {
        return (node ? (count(node->m_left) + count(node->m_right) + 1) : 0);
    }

    int height(QBTreeNode<T>* node) const
    {
        int ret = 0;

        if(node)
        {
            int hl = height(node->m_left);
            int hr = height(node->m_right);

            ret = ((hl > hr) ? hl : hr) + 1;
        }

        return ret;
    }

    int degree(QBTreeNode<T>* node) const
    {
        int ret = 0;

        if(node)
        {
            QBTreeNode<T>* child[] = {node->m_left, node->m_right};

            if(node->m_left) ret++;
            if(node->m_right) ret++;

            for(int i = 0; (i < 2) && (ret < 2); i++)
            {
                int dl = degree(child[i]);

                if(ret < dl) ret = dl;
            }
        }

        return ret;
    }

    QLinkList<T>* traversal(QBTreeNode<T>* node, BTTraversal order, QLinkList<T>* ret) const
    {
        if(node && ret)
        {
            switch (order)
            {
            case PreOrder:
                ret->insert(node->value);
                traversal(node->m_left, order, ret);
                traversal(node->m_right, order, ret);
                break;
            case InOrder:
                traversal(node->m_left, order, ret);
                ret->insert(node->value);
                traversal(node->m_right, order, ret);
                break;
            case PostOrder:
                traversal(node->m_left, order, ret);
                traversal(node->m_right, order, ret);
                ret->insert(node->value);
                break;
            default:
                THROW_EXCEPTION(QInvalidParameterException, "Paramer order isnot in enum BTTraversal...");
                break;
            }
        }

        return ret;
    }

    QBTreeNode<T>* clone(QBTreeNode<T>* node, QBTreeNode<T>* parent) const
    {
        QBTreeNode<T>* ret = NULL;

        if(node)
        {
            ret = QBTreeNode<T>::NewNode(node->value, parent);

            if(ret)
            {
                ret->m_left = clone(node->m_left, ret);
                ret->m_right = clone(node->m_right, ret);
            }
        }

        return ret;
    }

    bool equal(const QBTreeNode<T>* lr, const QBTreeNode<T>* rr) const
    {
        if(lr == rr) return true;
        if(lr == NULL || rr == NULL) return false;

        return ((lr->value == rr->value) && equal(lr->m_left, rr->m_left) && equal(lr->m_right, rr->m_right));
    }

    /*void traversal(BTTraversal order, LinkQueue<QBTreeNode<T>*>& queue) const
    {
        switch (order)
        {
        case PreOrder:
            queue->insert(node->value);
            traversal(node->m_left, order, ret);
            traversal(node->m_right, order, ret);
            break;
        case InOrder:
            traversal(node->m_left, order, ret);
            queue->insert(node->value);
            traversal(node->m_right, order, ret);
            break;
        case PostOrder:
            traversal(node->m_left, order, ret);
            traversal(node->m_right, order, ret);
            queue->insert(node->value);
            break;
        default:
            THROW_EXCEPTION(QInvalidParameterException, "Paramer order isnot in enum BTTraversal...");
            break;
        }
    }*/

public:
    QBTree()
    {

    }

    bool insert(QTreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    bool insert(QTreeNode<T>* node, BTNodePos pos)
    {
        return insert(dynamic_cast<QBTreeNode<T>*>(node), find(node->parent), pos);
    }

    bool insert(const T& value, QTreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    bool insert(const T& value, QTreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;

        QBTreeNode<T>* node = QBTreeNode<T>::NewNode(value, parent);

        if(node)
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if(ret == false)
            {
                delete node;
            }
        }
        else
        {
            ret = false;
            THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert tree node...");
        }

        return ret;
    }

    SharedPointer< QTree<T> > remove(const T& value)
    {
        QBTree<T>* ret = NULL;

        QBTreeNode<T>* node = find(value);

        if(node)
        {
            remove(node, ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(QInvalidParameterException, "Cannot find dest value in the tree...");
        }

        return ret;
    }

    SharedPointer< QTree<T> > remove(QTreeNode<T>* node)
    {
        QBTree<T>* ret = NULL;
        node = find(node);

        if(node)
        {
            remove(dynamic_cast<QBTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(QInvalidParameterException, "Cannot find dest node in the tree...");
        }

        return ret;
    }

    QBTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    QBTreeNode<T>* find(QTreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<QBTreeNode<T>*>(node));
    }

    QBTreeNode<T>* root() const
    {
        return dynamic_cast<QBTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        clear(root());

        this->m_queue.clear();
        this->m_root = NULL;
    }

    void begin() const
    {
        const_cast<LinkQueue<QBTreeNode<T>*>&>(m_queue).clear();

        if(root())
        {
            const_cast<LinkQueue<QBTreeNode<T>*>&>(m_queue).enqueue(root());
        }
    }

    void next() const
    {
        if(m_queue.length() > 0)
        {
            QBTreeNode<T>* node = m_queue.front();

            const_cast<LinkQueue<QBTreeNode<T>*>&>(m_queue).dequeue();

            if(node->m_left)
            {
                const_cast<LinkQueue<QBTreeNode<T>*>&>(m_queue).enqueue(node->m_left);
            }

            if(node->m_right)
            {
                const_cast<LinkQueue<QBTreeNode<T>*>&>(m_queue).enqueue(node->m_right);
            }
        }
    }

    bool end() const
    {
        return (m_queue.length() == 0);
    }

    T current() const
    {
        if(end())
        {
            THROW_EXCEPTION(QInvalidOperationException, "No value in current position...");
        }

        return m_queue.front()->value;
    }

    SharedPointer< QLinkList<T> > traversal(BTTraversal order) const
    {
        return traversal(root(), order, new QLinkList<T>());
    }

    SharedPointer< QBTree<T> > clone() const
    {
        QBTree<T>* ret = new QBTree<T>();

        if(ret)
        {
            ret->m_root = clone(root(), NULL);
        }

        return ret;
    }

    void operator delete(void* p)
    {
        QObject::operator delete(p);
    }

    bool operator ==(const QBTree<T>& btree) const
    {
        return equal(root(), btree.root());
    }

    bool operator !=(const QBTree<T>& btree) const
    {
        return !(*this == btree);
    }

    ~QBTree()
    {
        clear();
    }
};

}

#endif
