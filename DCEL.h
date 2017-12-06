#pragma once
#include <vector>
#include <tuple>
#include <memory>
using namespace std;

#ifndef point
#define point pair<double, double>
#define points vector<point>
#endif
#define middle(a, b) point((a.first + b.first) / 2, (a.second + b.second) / 2) 

struct Edge {
	Edge(const Edge &);
	Edge(point &p1, point &p2);
	Edge& operator=(const Edge&);
	point start;
	point end;
	pair<point, point> parents;	//input points that give a birth to the edge.
	int endsAmnt = 0;
};


class DCEL
{
public:
	DCEL()=default;
	~DCEL()=default;
	vector<Edge> getEdges()const;
	unsigned int push_Edge(point &, point &);
	void pop_Edge(unsigned int &);
	Edge& find_Edge(unsigned int &);
	int find_Edge(point &, bool);	// Second argument - isFirst
	Edge& operator[](unsigned int &);
	vector<Edge> *operator*();
	unsigned int size();
private:
	vector<Edge> edges;
};

