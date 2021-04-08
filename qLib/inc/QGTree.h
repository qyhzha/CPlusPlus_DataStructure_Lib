#ifndef __GTREE_H__
#define __GTREE_H__

#include "QTree.h"
#include "LinkQueue.h"
#include "GTreeNode.h"

namespace qLib
{

template <typename T>
class GTree : public QTree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* root, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(root != NULL)
        {
            if(root->value == value)
            {
                return root;
            }
            else
            {
                for(root->child.move(0); !root->child.end() && (ret == NULL); root->child.next())
                {
                    ret = find(root->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* root, GTreeNode<T>* node) const
    {
        GTreeNode<T>* ret = NULL;

        if((root != NULL) && (node != NULL))
        {
            if(root == node)
            {
                return root;
            }
            else
            {
                for(root->child.move(0); !root->child.end() && (ret == NULL); root->child.next())
                {
                    ret = find(root->child.current(), node);
                }
            }
        }

        return ret;
    }

    void clear(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                clear(node->child.current());
            }

            if(node->flag()) delete node;
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if(ret)
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                QLinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                child.remove(child.find(node));

                node->parent = NULL;
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to create new tree...");
        }
    }

    int count(GTreeNode<T>* root) const
    {
        int ret = 0;

        if(root != NULL)
        {
            if(root->child.length() > 0)
            {
                for(root->child.move(0); !root->child.end(); root->child.next())
                {
                    ret += count(root->child.current());
                }

                ret++;
            }
            else
            {
                ret = 1;
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* root) const
    {
        int ret = 0;

        if(root != NULL)
        {
            if(root->child.length() > 0)
            {
                for(root->child.move(0); !root->child.end(); root->child.next())
                {
                    int h = height(root->child.current());

                    if(h > ret)
                    {
                        ret = h;
                    }
                }

                ret = ret + 1;
            }
            else
            {
                ret = 1;
            }
        }

        return ret;
    }

    int degree(GTreeNode<T>* root) const
    {
        int ret = 0;

        if(root != NULL)
        {
            int len = root->child.length();

            if(len > 0)
            {
                for(root->child.move(0); !root->child.end(); root->child.next())
                {
                    int deg = degree(root->child.current());

                    if(deg > len)
                    {
                        len = deg;
                    }
                }

                ret = len;
            }
            else
            {
                ret = 1;
            }
        }

        return ret;
    }

public:
    GTree()
    {

    }

    bool insert(QTreeNode<T>* node)
    {
        bool ret = true;

        GTreeNode<T>* gnode = dynamic_cast<GTreeNode<T>*>(node);

        if(gnode != NULL)
        {
            if(this->m_root == NULL)
            {
                gnode->parent = NULL;
                this->m_root = gnode;
            }
            else if((this->m_root != NULL) && (gnode->parent != NULL))
            {
                GTreeNode<T>* parent = find(gnode->parent);

                if(parent)
                {
                    if(parent->child.find(gnode) < 0)
                    {
                        ret = parent->child.insert(gnode);
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else
                {
                    ret = false;
                    THROW_EXCEPTION(QInvalidParameterException, "Paramer tree node have invalid parent tree node...");
                }
            }
            else
            {
                ret = false;
                THROW_EXCEPTION(QInvalidParameterException, "Paramer tree node have invalid parent tree node...");
            }
        }
        else
        {
            ret = false;
            THROW_EXCEPTION(QInvalidParameterException, "Invalid paramer tree node...");
        }

        return ret;
    }

    bool insert(const T& value, QTreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = GTreeNode<T>::NewNode();

        if(node)
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node);
        }
        else
        {
            ret = false;
            THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to insert new tree node...");
        }

        return ret;
    }

    QSharedPointer<QTree<T>> remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

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

    QSharedPointer<QTree<T>> remove(QTreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        node = find(node);

        if(node)
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(QInvalidParameterException, "Cannot find dest value in the tree...");
        }

        return ret;
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(QTreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
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

        this->m_root = NULL;

        m_queue.clear();
    }

    void begin() const
    {
        if(root())
        {
            const_cast<LinkQueue<GTreeNode<T>*>&>(m_queue).clear();
            const_cast<LinkQueue<GTreeNode<T>*>&>(m_queue).enqueue(root());
        }
    }

    void next() const
    {
        if(m_queue.length() > 0)
        {
            GTreeNode<T>* node = m_queue.front();

            const_cast<LinkQueue<GTreeNode<T>*>&>(m_queue).dequeue();

            if(node->child.length() > 0)
            {
                for(node->child.move(0); !node->child.end(); node->child.next())
                {
                    const_cast<LinkQueue<GTreeNode<T>*>&>(m_queue).enqueue(node->child.current());
                }
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

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
