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
	Node(point &, Node *);
	double x;
	point pLeft;
	point pRight;
	Edge *edge;
	Node *Left = nullptr;
	Node *Right = nullptr;
	Node *Parent = nullptr;
	operator bool(); // is a Leaf.
	points operator()(double &);
	Node* opposite();
};

struct Event
{
	Event()=default;
	Event(point &);
	Event(point &, point &, Node*);
	point eventPoint;
	bool isSite = true;
	operator bool();
	point& operator*();
	point circleCenter;
	Node *node;
};

class EventQueue
{
public:
	EventQueue(points &);
	void push(point &, point &, Node*);	// For pushing circle event.
	point pop();
	bool empty();
	
private:
	bool isCircleEvent(Event &);
	struct Compare
	{
		bool operator()(Event &a, Event &b)
		{
			return a.eventPoint.second > b.eventPoint.second || a.eventPoint.second == b.eventPoint.second && a.eventPoint.first > b.eventPoint.first;
		}
	};
	priority_queue<Event, vector<Event>, Compare> queue;
	vector<point> addedPoints;

};

