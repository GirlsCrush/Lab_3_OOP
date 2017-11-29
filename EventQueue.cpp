#include "EventQueue.h"
using namespace std;

EventQueue::EventQueue(points & P)
{
	for (auto elem : P)
	{
		queue.push(elem);
	}
	
}


void EventQueue::push(point & p, point & center)
{
	queue.push(Event(p,center));
}

point EventQueue::pop()
{
	Event tmp = queue.top();
	if (tmp)
	{
		addedPoints.push_back(queue.top().eventPoint);
		queue.pop();
		return *tmp;
	}
	else
	{
		if (isCircleEvent(tmp))
		{
			queue.pop();
			return *tmp;
		}
		else
		{
			queue.pop();
			return EventQueue::pop();
		}
	}
}

bool EventQueue::isCircleEvent(Event &event)
{
	
}

EventQueue::Event::Event(point &p1)
{
	eventPoint = p1;
	isSite = true;
}

EventQueue::Event::Event(point &p1, point &p2)
{
	eventPoint = p1;
	circleCenter = p2;
	isSite = false;
}

EventQueue::Event::operator bool()
{
	return isSite;
}

point& EventQueue::Event::operator*()
{
	return eventPoint;
}

