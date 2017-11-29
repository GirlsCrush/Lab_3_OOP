#pragma once
#include <tuple>
#include <vector>
#include <queue>


using namespace std;
#define point pair<double, double>
#define points vector<pair<double, double>>


class EventQueue
{
public:
	EventQueue(points &);
	void push(point &, point &);	// For pushing circle event.
	point pop();

	struct Event
	{
		Event(point &);
		Event(point &, point &);
		point eventPoint;
		bool isSite = true;
		operator bool();
		point& operator*();
		point circleCenter;
	};

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

