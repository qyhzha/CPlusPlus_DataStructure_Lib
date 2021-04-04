#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "QGraph.h"
#include "QLinkList.h"

namespace qLib
{
	
template <typename V, typename E>
class QListGraph : QGraph<V, E>
{
protected:
	struct Vertex : public QObject
	{
		V* data;
		QLinkList< Edge<E> > edge;
		
		Vertex()
		{
			data = NULL;
		}
	};
	
	QLinkList< Vertex* > m_list;
	
public:
	QListGraph(unsigned int n = 0)
	{
		for(unsigned int i = 0; i < n; i++)
		{
			addVertex();
		}
	}
	
	int addVertex()
	{
		int ret = -1;
		Vertex* v = new Vertex();
		
		if(v != NULL)
		{
			m_list.insert(v);
			
			ret = m_list.length() - 1;
		}
		else
		{
			THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to create new Vertex QObject...");
		}
		
		return ret;
	}
	
	int addVertex(const V& value)
	{
		int ret = addVertex();
		
		if(ret >= 0)
		{
			setVertex(ret, value);
		}
		
		return ret;
	}
	
	bool setVertex(int i, const V& obj)
	{
		bool ret = (0 <= i) && (i < vCount());
		
		if(ret)
		{
			Vertex* vertex = m_list.get(i);
			V* data = vertex->data;
			
			if(data == 0)
			{
				data = new V();
			}
			
			if(data != 0)
			{
				*data = obj;
				vertex->data = data;
			}
			else
			{
				THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to create new Vertex value...");
			}
		}
		
		return ret;
	}
	
	V getVertex(int i) const
	{
		V ret;
		bool ok = getVertex(i, ret);
		
		if(!ok)
		{
			THROW_EXCEPTION(QInvalidParameterException, "Invalid parameter...");
		}
		
		return ret;
	}
	
	bool getVertex(int i, V& obj) const
	{
		bool ret = (0 <= i) && (i < vCount());
		
		if(ret)
		{
			Vertex* vertex = m_list.get(i);
			
			if(vertex->data)
			{
				obj = *(vertex->data);
			}
			else
			{
				ret = false;
			}			
		}
		
		return ret;
	}
	
	void removeVertex()
	{
		int index = vCount() - 1;
		
		for(int i = 0; i < index; i++)
		{
			Vertex* vertex = m_list.get(i);
			Edge<E>& edge = vertex.edge;
			
			for(int j = 0; j < edge.length(); i++)
			{
				if(edge.get(i).e == index)
				{
					edge.remove(i);
				}
			}
		}
		
		m_list.remove(index);
	}
	
	QSharedPointer< QLinkList<int> > getAdjacent(int i)
	{
		QLinkList<int>* ret = new QLinkList<int>();
		bool ok = (0 <= i) && (i < vCount());
		
		if(ok)
		{
			Vertex* vertex = m_list.get(i);
			
			if(vertex)
			{
				for((vertex->edge).move(0); !((vertex->edge).end()); (vertex->edge).next())
				{
					ret->insert((vertex->edge).current().e);
				}
			}
		}		
		
		return ret;
	}
	
	int addEdge(int i, int j)
	{		
		return ((0 <= i) && (i < vCount())) ? (m_list[i].edge.insert(m_list[i].edge.length(), Edge<E>(i, j)), m_list[i].edge.length() - 1) : -1;
	}
	
	int addEdge(int i, int j, const E& obj)
	{
		return ((0 <= i) && (i < vCount())) ? (m_list[i]->edge.insert(m_list[i]->edge.length(), Edge<E>(i, j, obj)), (m_list[i]->edge.length() - 1)) : -1;
	}
	
    E getEdge(int i, int j) const
    {
    	E ret;
    	bool ok = getEdge(i, j, ret);
    	
    	if(!ok)
    	{
    		THROW_EXCEPTION(QInvalidParameterException, "Invalid parameter...");
		}
    	
    	return ret;
	}
	
    bool getEdge(int i, int j, E& obj) const
    {
        if((0 <= i) && (i < vCount()) && (0 <= j) && (j < m_list.get(i)->edge.length()))
        {
            obj = m_list.get(i)->edge.get(j).data;
            return true;
        }

        THROW_EXCEPTION(QInvalidParameterException, "Parameter i or j is invalid.");
        return false;
	}
	
    bool setEdge(int i, int j, const E& obj)
    {
        return ((0 <= i) && (i < vCount()) && (0 <= j) && (j < m_list.get(i)->edge.length())) ? (m_list.get(i)->edge[j].data = obj, true) : false;
	}
	
    bool removeEdge(int i, int j)
    {
    	return ((0 <= i) && (i < vCount()) && (0 <= j) && (j < m_list.get(i)->edge.length())) ? m_list.get(i)->edge.remove(j) : false;
	}
	
    int vCount() const
    {
    	return m_list.length();
	}
	
    int eCount() const
    {
    	int ret = 0;
    	
    	for(m_list.move(0); !m_list.end(); m_list.next())
    	{
    		ret += m_list.current()->edge.length();
		}
		
		return ret;
	}
	
    int OD(int i) const
    {
    	return m_list.get(i)->edge.length();
	}
	
    int ID(int i) const
    {
    	int ret = 0;
    	
    	if((0 <= i) && (i < vCount()))
    	{
    		for(m_list.move(0); !m_list.end(); m_list.next())
    		{
    			for(m_list.current()->edge.move(0); !m_list.current()->edge.end(); m_list.current()->edge.next())
    			{
    				if(m_list.current()->edge.current().e == i)
    				{
    					ret++;
					}
				}
			}
		}
    	
    	return ret;
	}
	
	~QListGraph()
	{
		for(m_list.move(0); !m_list.end(); m_list.next())
		{
			if(m_list.current()->data != NULL)
			{
				delete m_list.current()->data;
			}
			
			delete m_list.current();
		}
	}
};
	
};

#endif
