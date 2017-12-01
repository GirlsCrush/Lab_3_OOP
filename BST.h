#pragma once

#include "EventQueue.h"

using namespace std;

class BST
{
public:
	void drawDiagram();
	BST(points &);
private:
	Node *root = nullptr;
	DCEL diagram;
	EventQueue events;
	points beachLine;

	void addCircleEvent(point, Node*, point);
	Node *findArc(double &, Node *);
	points findNieghbors(Node *);
	void update(Node*, double &);
	
	void update(double &);
	void addSite(Event &);
	void handleCircleEvent(Event &);
};

