#include "DCEL.h"



vector<Edge> DCEL::getEdges() const
{
	return edges;
}

unsigned int DCEL::push_Edge(point &p1, point &p2)
{
	/*int indexP1 = find_Edge(p1, true);
	int indexP2 = find_Edge(p2, true);
	if (indexP1 != size()) return indexP1;
	if (indexP2 != size()) return indexP2;*/
	edges.push_back(Edge(p1, p2));
	return edges.size() - 1;
}

void DCEL::pop_Edge(unsigned int &i)
{
	edges[i].endsAmnt++;
}

Edge& DCEL::find_Edge(unsigned int &i)
{
	return edges[i];
}

int DCEL::find_Edge(point &p1, bool isFirst)
{
	int i = 0;
	if (isFirst)
	{
		for (i = 0; i < edges.size(); i++)
		{
			if (edges[i].parents.first == p1) return i;
		}
	}
	else
	{
		for (i = 0; i < edges.size(); i++)
		{
			if (edges[i].parents.second == p1) return i;
		}
	}
	return i;
}

Edge & DCEL::operator[](unsigned int &i)
{
	return edges[i];
}

vector<Edge>* DCEL::operator*()
{
	return &edges;
}

unsigned int DCEL::size()
{
	return edges.size();
}


Edge::Edge(const Edge &edge)
{
	start = edge.start;
	end = edge.end;
	parents = edge.parents;
	endsAmnt = edge.endsAmnt;
}

Edge::Edge(point &p1, point &p2)
{
	parents.first = p1;
	parents.second = p2;
}

Edge & Edge::operator=(const Edge &edge)
{
	start = edge.start;
	end = edge.end;
	parents = edge.parents;
	endsAmnt = edge.endsAmnt;
	return *this;
}

