#include "EventQueue.h"
using namespace std;
#define PRECISION 0.00000001

Node::Node(point &site, Node *parent, vector<Edge> *cont)
{
	pLeft = site;
	Parent = parent;
	x = site.first;
	container = cont;
}

Node::Node(point &site, Node *parent, vector<Edge> *cont, unsigned int & newEdge)
{
	pLeft = site;
	Parent = parent;
	x = site.first;
	container = cont;
	edge = newEdge;
}
Node::operator bool()
{
	return Left == Right && Right == nullptr;
}

Node * Node::opposite()
{
	if ((*this).Parent == nullptr) return nullptr;
	if (this == (*(*this).Parent).Left) return (*(*this).Parent).Right;
	else return (*(*this).Parent).Left;
}

Edge & Node::getEdge()
{
	return (*container)[edge];
}

EventQueue::EventQueue(points & P)
{
	for (auto elem : P)
	{
		queue.emplace(elem);
	}
	
}


void EventQueue::push(point & p, point & center, Node *lowerNode, Node *disNode, Node *upperNode)
{
	queue.push(Event(p, center, lowerNode, disNode, upperNode));
}

Event EventQueue::pop()
{
	Event tmp = queue.top();
	if (tmp)
	{
		addedPoints.push_back(queue.top().eventPoint);
		queue.pop();
	}
	else
	{
		if (!isCircleEvent(tmp))
		{
			queue.pop();
			if (queue.empty())
			{
				tmp.circleCenter = tmp.eventPoint;
				return tmp;
			}
			return EventQueue::pop();
		}
		else queue.pop();
	}
	return tmp;
}

bool EventQueue::empty()
{
	return queue.empty();
}

points EventQueue::getAddedPoints()
{
	return addedPoints;
}

void EventQueue::init(points & p)
{
	for (int i = 0; i < p.size(); i++) queue.emplace(p[i]);
}

bool EventQueue::isCircleEvent(Event &event)
{
	for (int i = addedPoints.size() - 1; i >= 0 ; i--)
	{
		//Checks if there is any input point inside the Circle. Got from circle equation.
		if (((event.eventPoint.second - event.circleCenter.second) * (event.eventPoint.second - event.circleCenter.second) - 
			(addedPoints[i].first - event.circleCenter.first) * (addedPoints[i].first - event.circleCenter.first) -
			(addedPoints[i].second - event.circleCenter.second) * (addedPoints[i].second - event.circleCenter.second)) > PRECISION)
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

Event::Event(point & p, point & center, Node *_lowerNode, Node *_disNode, Node *_upperNode)
{
	eventPoint = p;
	circleCenter = center;
	lowerNode = _lowerNode;
	disNode = _disNode;
	upperNode = _upperNode;
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

