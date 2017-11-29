#include "DCEL.h"



DCEL::DCEL()
{
}


DCEL::~DCEL()
{
}

void DCEL::update(double y)
{
}

Edge* DCEL::push_Edge(point &p1, point &p2)
{
	unc_edges.push_back(Edge(p1, p2));
	return &(unc_edges.back());
}

void DCEL::pop_uncEdge(point &p1, point &p2)
{
	set<point> temp = { p1, p2 };
	for (int i = 0; i < unc_edges.size(); i++)
	{
		if (unc_edges[i].parents == temp) 
		{
			edges.push_back(unc_edges[i]);
			unc_edges.erase(unc_edges.begin() + i);
		}
	}
}

Edge *DCEL::find_uncEdge(point &p1, point &p2)
{
	set<point> temp = { p1, p2 };
	for (int i = 0; i < unc_edges.size(); i++)
	{
		if (unc_edges[i].parents == temp) return &unc_edges[i];
	}
}

Edge::Edge(const Edge &edge) 
{
	parents = edge.parents;
}

Edge::Edge(point &p1, point &p2)
{
	start.reset(new middle(p1, p2));
	parents.insert(p1);
	parents.insert(p2);
}

