#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"
#include "LinkList.h"
#include "SharedPointer.h"

namespace QinLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template <typename T>
class BTree : Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    virtual BTreeNode<T>* find(BTreeNode<T>* root, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

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

    virtual BTreeNode<T>* find(BTreeNode<T>* root, BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

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

    virtual bool insert(BTreeNode<T>* node, BTreeNode<T>* parent, BTNodePos pos)
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
                THROW_EXCEPTION(InvalidParameterException, "Paramer tree node hava a invalid parent tree node...");
            }
        }
        else
        {
            ret = false;
            THROW_EXCEPTION(InvalidParameterException, "Invalid paramer tree node...");
        }

        return ret;
    }

    virtual void clear(BTreeNode<T>* node)
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

    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if(ret)
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

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
                    THROW_EXCEPTION(InvalidParameterException, "Paramer tree node have a invalid parent tree node...");
                }
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new tree...");
        }
    }

    int count(BTreeNode<T>* node) const
    {
        return (node ? (count(node->m_left) + count(node->m_right) + 1) : 0);
    }

    int height(BTreeNode<T>* node) const
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

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node)
        {
            BTreeNode<T>* child[] = {node->m_left, node->m_right};

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

    LinkList<T>* traversal(BTreeNode<T>* node, BTTraversal order, LinkList<T>* ret) const
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
                THROW_EXCEPTION(InvalidParameterException, "Paramer order isnot in enum BTTraversal...");
                break;
            }
        }

        return ret;
    }

    BTreeNode<T>* clone(BTreeNode<T>* node, BTreeNode<T>* parent) const
    {
        BTreeNode<T>* ret = NULL;

        if(node)
        {
            ret = BTreeNode<T>::NewNode(node->value, parent);

            if(ret)
            {
                ret->m_left = clone(node->m_left, ret);
                ret->m_right = clone(node->m_right, ret);
            }
        }

        return ret;
    }

    bool equal(const BTreeNode<T>* lr, const BTreeNode<T>* rr) const
    {
        if(lr == rr) return true;
        if(lr == NULL || rr == NULL) return false;

        return ((lr->value == rr->value) && equal(lr->m_left, rr->m_left) && equal(lr->m_right, rr->m_right));
    }

    /*void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue) const
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
            THROW_EXCEPTION(InvalidParameterException, "Paramer order isnot in enum BTTraversal...");
            break;
        }
    }*/

public:
    BTree()
    {

    }

    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        return insert(dynamic_cast<BTreeNode<T>*>(node), find(node->parent), pos);
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode(value, parent);

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
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert tree node...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = NULL;

        BTreeNode<T>* node = find(value);

        if(node)
        {
            remove(node, ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Cannot find dest value in the tree...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;
        node = find(node);

        if(node)
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Cannot find dest node in the tree...");
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
        const_cast<LinkQueue<BTreeNode<T>*>&>(m_queue).clear();

        if(root())
        {
            const_cast<LinkQueue<BTreeNode<T>*>&>(m_queue).enqueue(root());
        }
    }

    void next() const
    {
        if(m_queue.length() > 0)
        {
            BTreeNode<T>* node = m_queue.front();

            const_cast<LinkQueue<BTreeNode<T>*>&>(m_queue).dequeue();

            if(node->m_left)
            {
                const_cast<LinkQueue<BTreeNode<T>*>&>(m_queue).enqueue(node->m_left);
            }

            if(node->m_right)
            {
                const_cast<LinkQueue<BTreeNode<T>*>&>(m_queue).enqueue(node->m_right);
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
            THROW_EXCEPTION(InvalidOperationException, "No value in current position...");
        }

        return m_queue.front()->value;
    }

    SharedPointer< LinkList<T> > traversal(BTTraversal order) const
    {
        return traversal(root(), order, new LinkList<T>());
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret)
        {
            ret->m_root = clone(root(), NULL);
        }

        return ret;
    }

    void operator delete(void* p)
    {
        Object::operator delete(p);
    }

    bool operator ==(const BTree<T>& btree) const
    {
        return equal(root(), btree.root());
    }

    bool operator !=(const BTree<T>& btree) const
    {
        return !(*this == btree);
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
