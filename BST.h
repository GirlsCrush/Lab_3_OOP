#pragma once
#include <Windows.h>
#include <GL\glew.h>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include "EventQueue.h"
#include <iostream>

#define ORTO 10

using namespace std;

class BST
{
public:
	BST() = default;
	double updateDiagram();
	void updateIndent(double &);
	BST(points &);
	vector<Edge> getEdges();
	points getBeachLine();
	points getAddedPoints();
	operator bool();
	void init(points &);
private:
	Node *root = nullptr;
	DCEL diagram;
	EventQueue events;
	points beachLine;
	
	void addCircleEvent(Node*, Node*, Node*);
	Node *findArc(double &, Node *);
	Node *findLeftNeighbor(Node *);
	Node *findLeftNeighbor(double &, Node *);
	Node *findRightNeighbor(Node *);
	Node *findRightNeighbor(double &, Node *);
	vector<Node*> findNieghbors(Node *);
	void update(Node*, double &);
	void update(double);
	void addSite(Event &);
	void handleCircleEvent(Event &);
};
