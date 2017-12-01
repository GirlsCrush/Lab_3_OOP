#include "EventQueue.h"
using namespace std;

EventQueue::EventQueue(points & P)
{
	for (auto elem : P)
	{
		queue.push(elem);
	}
	
}


void EventQueue::push(point & p, point & center, Node *newNode)
{
	queue.push(Event(p,center, newNode));
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

bool EventQueue::empty()
{
	return queue.empty();
}

bool EventQueue::isCircleEvent(Event &event)
{
	for (int i = addedPoints.size() - 1; i >= 0 ; i--)
	{
		//Checks if there is any input point inside the Circle. Got from circle equation.
		if ((addedPoints[i].first - event.circleCenter.first) * (addedPoints[i].first - event.circleCenter.first) +
			(addedPoints[i].second - event.circleCenter.second) * (addedPoints[i].second - event.circleCenter.second) <
			(event.eventPoint.second - event.circleCenter.second) * (event.eventPoint.second - event.circleCenter.second))
		{
			return false;
		}
	}
	return true;
}

Event::Event(point &p1)
{
	eventPoint = p1;
	isSite = true;
}

Event::Event(point &p1, point &p2, Node *newNode)
{
	eventPoint = p1;
	circleCenter = p2;
	node = newNode;
	isSite = false;
}

Event::operator bool()
{
	return isSite;
}

point& Event::operator*()
{
	return eventPoint;
}

