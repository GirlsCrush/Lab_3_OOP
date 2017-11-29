#include "BST.h"



BST::BST()
{
}


BST::~BST()
{
}

void BST::addLeaf(point &)
{
}

void BST::addLeaf(point &p1)
{
	if (Root.Left == nullptr && Root.Right == nullptr)
	{
		Root.Left = new Node(p1, &Root);

	}
	else if(Root.Right == nullptr)
}

Node::Node(point & p1, Node *node)
{
	p = p1;
	x = p.first;
	Parent = node;
}
