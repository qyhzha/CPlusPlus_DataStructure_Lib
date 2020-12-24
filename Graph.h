#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "Exception.h"
#include "SharedPointer.h"
#include "LinkList.h"

namespace QinLib
{

template <typename E>
struct Edge : public Object
{
	int b;
	int e;
	E data;
	
	Edge(int i = -1, int j = -1)
	{
		b = i;
		e = j;
	}
	
	Edge(int i, int j, const E& value)
	{
		b = i;
		e = j;
		data = value;
	}
	
	bool operator ==(const Edge<E>& obj) const
	{
		return (b == obj.b) && (e == obj.e) && (data == obj.data);
	}
};

template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) const = 0;
    virtual bool getVertex(int i, V& obj) const = 0;
    virtual bool setVertex(int i, const V& obj) = 0;
    virtual SharedPointer< LinkList<int> > getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) const = 0;
    virtual bool getEdge(int i, int j, E& obj) const = 0;
    virtual bool setEdge(int i, int j, const E& obj) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() const = 0;
    virtual int eCount() const = 0;
    virtual int OD(int i) const = 0;
    virtual int ID(int i) const = 0;
    int TD(int i) const {return OD(i) + ID(i);}
};

}

#endif // GRAPH_H
