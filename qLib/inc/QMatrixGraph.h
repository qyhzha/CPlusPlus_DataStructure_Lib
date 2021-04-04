#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "QGraph.h"

namespace qLib
{

template <typename V, typename E, int N>
class MatrixGraph : public QGraph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_count;

public:
    MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_count = 0;
    }

    V getVertex(int i) const
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
        }

        return ret;
    }

    bool getVertex(int i, V& obj) const
    {
        bool ret = (i >= 0) && (i < vCount());

        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                obj = *(m_vertexes[i]);
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& obj)
    {
        bool ret = (i >= 0) && (i < vCount());

        if(ret)
        {
            if(m_vertexes[i] == NULL) m_vertexes[i] = new V();

            if(m_vertexes[i] != NULL)
            {
                *(m_vertexes[i]) = obj;
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    QSharedPointer< QLinkList<int> > getAdjacent(int i)
    {
    	QLinkList<int>* ret = NULL;
    	
    	if( (i >= 0) && (i < vCount()) )
    	{
    		ret = new QLinkList<int>();
    		
    		if(ret)
    		{
    			for(int j = 0; j < vCount(); j++)
    			{
    				if(m_edges[i][j] != NULL)
    				{
    					ret->insert(j); 
					}
				}
			}
			else
			{
				THROW_EXCEPTION(QNoEnoughMemoryException, "No enough memory to create QLinkList<int> QObject...");
			}
		}
		else
		{
			THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
		}
    	
        return ret;
    }

    E getEdge(int i, int j) const
    {
		E ret;
		
		if(!getEdge(i, j, ret))
		{
			THROW_EXCEPTION(QInvalidParameterException, "Paramer i is invalid...");
		}
		
		return ret;
    }

    bool getEdge(int i, int j, E& obj) const
    {
		bool ret = (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount());
		
		if(ret)
		{
			if(m_edges[i][j] != NULL)
			{
				obj = *m_edges[i][j];
			}
			else
			{
				ret = false;
			}
		}
		
		return ret;
    }

    bool setEdge(int i, int j, const E& obj)
    {
       	bool ret = (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount());
       
        if(ret)
        {
            if(m_edges[i][j] == NULL) 
			{
				m_edges[i][j] = new E();
				
				if(m_edges[i][j] != NULL)
				{
					m_count++;
				}
			}

            if(m_edges[i][j] != NULL)
            {
                *(m_edges[i][j]) = obj;
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    { 
		bool ret = (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount());
		
		if(ret)
		{
			if(m_edges[i][j] != NULL)
			{
				E* toDel = m_edges[i][j];
				
				m_edges[i][j] = NULL; 
				m_count--;
				
				delete toDel;
			}
		}
		
		return ret;
    }

    int vCount() const
    {
        return N;
    }

    int eCount() const
    {
		return m_count;
    }

    int OD(int i) const
    {
		int ret = -1;
		
		if( (i >= 0) && (i < vCount()) )
		{
			ret = 0;
			
			for(int j = 0; j < vCount(); j++)
			{
				if(m_edges[i][j] != NULL)
				{
					ret++;
				}
			}
		} 
		
		return 0;
    }

    int ID(int i) const
    {
		int ret = -1;
		
		if( (i >= 0) && (i < vCount()) )
		{
			ret = 0;
			
			for(int j = 0; j < vCount(); j++)
			{
				if(m_edges[j][i] != NULL)
				{
					ret++;
				}
			}
		} 
		
		return 0;
    }

    ~MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {
            for(int j = 0; j < vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }
};

}

#endif // MATRIXGRAPH_H
