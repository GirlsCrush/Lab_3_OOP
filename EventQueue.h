#pragma once
#include <tuple>
#include <vector>
#include <queue>
#include "DCEL.h"

using namespace std;
#ifndef point

#define point pair<double, double>
#define points vector<pair<double, double>>

#endif 

struct Node
{
	Node(point &, Node *, vector<Edge> *);
	Node(point &, Node *, vector<Edge> *, unsigned int &);
	double x;
	point pLeft;
	point pRight;
	unsigned int edge;
	vector<Edge> *container;
	Node *Left = nullptr;
	Node *Right = nullptr;
	Node *Parent = nullptr;
	operator bool(); // is a Leaf.
	points operator()(double &);
	Node* opposite();
	Edge& getEdge();
};

struct Event
{
	Event()=default;
	Event(point &);
	Event(point &, point &, Node*, Node*, Node*);
	point eventPoint;
	bool isSite = true;
	point circleCenter;
	Node *lowerNode;
	Node *disNode;
	Node *upperNode;

	operator bool();
	point& operator*();
	
};

class EventQueue
{
public:
	EventQueue() = default;
	EventQueue(points &);
	void push(point &, point &, Node*, Node*, Node*);	// For pushing circle event.
	Event pop();
	bool empty();
	points getAddedPoints();
	void init(points &);
private:
	bool isCircleEvent(Event &);
	struct Compare
	{
		bool operator()(Event a, Event b)
		{
			return a.eventPoint.second < b.eventPoint.second; /*|| a.eventPoint.second == b.eventPoint.second && a.eventPoint.first < b.eventPoint.first;*/
		}
	};
	priority_queue<Event, vector<Event>, Compare> queue;
	vector<point> addedPoints;

};

