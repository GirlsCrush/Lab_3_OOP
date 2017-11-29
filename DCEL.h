#pragma once
#include <vector>
#include <tuple>
#include <memory>
#include <set>
using namespace std;

#ifndef point
#define point pair<double, double>
#define points vector<point>
#endif
#define middle(a, b) point((a.first + b.first) / 2, (a.second + b.second) / 2) 

struct Edge {
	Edge(const Edge &);
	Edge(point &p1, point &p2);
	unique_ptr<point> start = nullptr;
	unique_ptr<point> end = nullptr;
	set<point> parents;	//input points that give a birth to the edge.
};


class DCEL
{
public:
	DCEL();
	~DCEL();
	void update(double y);
	Edge* push_Edge(point &, point &);
	void pop_uncEdge(point &, point &);
	vector<Edge> unc_edges;	// Uncomplete edges.
	vector<Edge> edges;		// Complete edges.	
	Edge *find_uncEdge(point &, point &);
};

