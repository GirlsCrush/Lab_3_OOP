#pragma once
#include "DCEL.h"

struct Node
{
	Node(point &, Node *);
	double x;
	point p;
	Node *Left = nullptr;
	Node *Right = nullptr;
	Node *Parent = nullptr;
	bool isLeaf = true;
};

class BST
{
public:
	BST();
	~BST();
	void addLeaf(point &);
	Node Root;
	
};

