#include "DCEL.h"



Edge* DCEL::push_Edge(point &p1, point &p2)
{
	unc_edges.push_back(Edge(p1, p2));
	return &(unc_edges.back());
}

void DCEL::pop_uncEdge(point &p1, point &p2)
{
	int edgeIndex = find_uncEdge(p1, p2);
	unc_edges[edgeIndex].endsAmnt++;
	if (unc_edges[edgeIndex].endsAmnt == 2)
	{
		edges.push_back(unc_edges[edgeIndex]);
		unc_edges.erase(unc_edges.begin() + edgeIndex);
	}
}

int DCEL::find_uncEdge(point &p1, point &p2)
{
	set<point> temp1 = { p1, p2 };
	set<point> temp2 = { p2, p1 };
	for (int i = 0; i < unc_edges.size(); i++)
	{
		if (unc_edges[i].parents == temp1 || unc_edges[i].parents == temp2) return i;
	}
}
//
//Edge::Edge(const Edge &edge) 
//{
//	parents = edge.parents;
//}

Edge::Edge(point &p1, point &p2)
{
	start.reset(new middle(p1, p2));
	parents.insert(p1);
	parents.insert(p2);
}

