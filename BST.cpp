#include "BST.h"
#define BEACH_LINE_PRECISION 100
#define BOTTOM_INDENT 100.
#define dist(p1, p2) sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second))

void BST::addSite(Event &siteEvent)
{
	point site = siteEvent.eventPoint;
	if (!root)
	{
		root = new Node(site, nullptr);
		return;
	}
	Node *upSite = findArc(site.first, root);
	points neighbors = findNieghbors(upSite);
	Edge* newEdge = diagram.push_Edge(site, (*upSite).pLeft);
	

	if ((*upSite).x > site.first)
	{
		(*upSite).pRight = site;
		(*upSite).edge = newEdge;
		(*upSite).Left = new Node((*upSite).pLeft, upSite);
		(*upSite).Right = new Node(site, upSite);
		(*(*upSite).Right).pRight = (*upSite).pLeft;
		(*(*upSite).Right).Left = new Node(site, (*upSite).Right);
		(*(*upSite).Right).Right = new Node((*upSite).pLeft, (*upSite).Right);
		(*(*upSite).Right).edge = newEdge;
		if (neighbors.size() >= 1) addCircleEvent(site, (*upSite).Left, neighbors[0]);
		if (neighbors.size() >= 2) addCircleEvent(site, (*(*upSite).Right).Right, neighbors[1]);
		
	
	}
	else
	{
		(*upSite).pRight = (*upSite).pLeft;
		(*upSite).pLeft = site;
		(*upSite).edge = newEdge;
		(*upSite).Left = new Node((*upSite).pRight, upSite);
		(*upSite).Right = new Node((*upSite).pRight, upSite);
		(*(*upSite).Left).pRight = site;
		(*(*upSite).Left).Right = new Node(site, (*upSite).Right);
		(*(*upSite).Left).Left = new Node((*upSite).pRight, (*upSite).Right);
		(*(*upSite).Left).edge = newEdge; 
		if (neighbors.size() >= 1) addCircleEvent(site, (*(*upSite).Left).Left, neighbors[0]);
		if (neighbors.size() >= 2) addCircleEvent(site, (*upSite).Right, neighbors[1]);
	}
	
}

void BST::handleCircleEvent(Event &circleEvent)
{
	Node *node = circleEvent.node;
	Node *opposite = (*node).opposite();
	bool isOppositeLeaf = bool(*opposite);
	bool isNodeLeft = (*(*node).Parent).Left == node;
	bool isParentLeft = (isOppositeLeaf ? (*(*node).Parent).Parent == (*(*(*node).Parent).Parent).Left : (*node).Parent == (*(*(*node).Parent).Parent).Left);
	(*opposite).Parent = (*(*node).Parent).Parent;
	delete (*node).Parent;
	delete node;
	if (!isParentLeft)
	{
		if (isOppositeLeaf && isNodeLeft) (*(*(*opposite).Parent).Parent).pRight = (*opposite).pLeft;
		if (!isOppositeLeaf && isNodeLeft) (*(*opposite).Parent).pRight = (*(*opposite).Left).pLeft;
	}
	if (isParentLeft)
	{
		if (!isOppositeLeaf && !isNodeLeft)(*(*opposite).Parent).pLeft = (*(*opposite).Right).pLeft;
		if (isOppositeLeaf && !isNodeLeft)  (*(*(*opposite).Parent).Parent).pLeft = (*opposite).pLeft;
	}
	if (isOppositeLeaf) diagram.pop_uncEdge((*(*opposite).Parent).pLeft, (*(*opposite).Parent).pRight);
	else diagram.pop_uncEdge((*opposite).pLeft, (*opposite).pRight);
}

BST::BST(points &input): events(input)
{
}

void BST::drawDiagram()
{
	Event tmp = events.pop();
	addSite(tmp);
	while (!events.empty())
	{
		tmp = events.pop();
		if (tmp) addSite(tmp);
		else handleCircleEvent(tmp);
		update(tmp.eventPoint.second);
		// Part of code which draws diagram.
	}
	tmp.eventPoint.second -= BOTTOM_INDENT;
	update((tmp.eventPoint.second));
}

void BST::update(double &y)
{
	update(root, y);
}

void BST::addCircleEvent(point p1, Node* node, point p3)
{
	point p2 = (*node).pLeft;
	if (p1.first == p2.first && p2.first == p3.first || p1.second == p2.second && p2.second == p3.second) return;
	double a1 = (p2.first - p1.first) / (p1.second - p2.second);
	double a2 = (p1.first + p2.first) / 2;
	double a3 = (p1.second + p2.second) / 2;
	double b1 = (p3.first - p2.first) / (p2.second - p3.second);
	double b2 = (p3.first + p2.first) / 2;
	double b3 = (p3.second + p2.second) / 2;
	double x = (a1 * a2 - b1 * b2 + b3 - a3) / (a1 - b1);
	double y = a1 * (x - a2) + a3;
	double y1 = y - sqrt((p1.first - x) * (p1.first - x) + (p1.second - y) * (p1.second - y));
	events.push(point(x, y1), point(x, y), node);
}

Node * BST::findArc(double &siteX, Node *node)
{
	if (node) return node;
	if (siteX < (*node).x) return findArc(siteX, (*node).Left);
	return findArc(siteX, (*node).Right);
}

points BST::findNieghbors(Node * center)
{
	if(!(*center).Parent) return points();
	points neighbors;
	if ((*(*center).Parent).Left == center)
	{
		neighbors.push_back((*(*center).Parent).pRight);
		if (!(*(*center).Parent).Parent) return neighbors;
		neighbors.push_back((*(*(*center).Parent).Parent).pLeft);
		return neighbors;
	}
	else
	{
		neighbors.push_back((*(*center).Parent).pLeft);
		if (!(*(*center).Parent).Parent) return neighbors;
		neighbors.insert(neighbors.begin(), (*(*(*center).Parent).Parent).pRight);
		return neighbors;
	}
}

void BST::update(Node *node, double &y)
{
	points arc = (*node)(y);
	for (int i = 0; i < arc.size(); i++) beachLine.emplace_back(arc[0]);
	if (!(*node))
	{
		update((*node).Left, y);
		update((*node).Right, y);
	}
}

Node::Node(point &site, Node *parent)
{
	pLeft = site;
	Parent = parent;
	x = site.first;
}

Node::operator bool()
{
	return Left == Right && Right == nullptr;
}

vector<point> Node::operator()(double & y)
{
	if (!(*this))
	{
		double a_1 = 1 / (2 * (pLeft.second - y));
		double a_2 = 1 / (2 * (pRight.second - y));
		double b_1 = (pLeft.second + y) / 2;
		double b_2 = (pRight.second + y) / 2;
		double discr = 4 * ((a_1 * pLeft.first - a_2 * pRight.first) * (a_1 * pLeft.first - a_2 * pRight.first) -
			(a_1 - a_2) * (pLeft.first * pLeft.first - pRight.first * pRight.first + b_1 - b_2));
		double x_1 = (a_2 * pRight.first - a_1 * pLeft.first - sqrt(discr / 4)) / (a_1 - a_2);
		double x_2 = (a_2 * pRight.first - a_1 * pLeft.first + sqrt(discr / 4)) / (a_1 - a_2);

		if (pLeft.first < pRight.first)
		{
			x = (x_1 < x_2 ? x_1 : x_2);
			(*((*edge).end)) = point(x, a_1 * (x - pLeft.first) * (x - pLeft.first) + b_1);
		}
		else
		{
			x = (x_1 < x_2 ? x_2 : x_1);
			(*((*edge).start)) = point(x, a_1 * (x - pLeft.first) * (x - pLeft.first) + b_1);
		}
		return points();
	}
	else
	{
		double leftLim;
		double rightLim;
		if (this == (*(*this).Parent).Left)
		{
			rightLim = (*(*this).Parent).x;
			if ((*(*(*this).Parent).Parent).Right == (*this).Parent) leftLim = (*(*(*this).Parent).Parent).x;
			else leftLim = rightLim - pLeft.first;
		}
		else
		{
			leftLim = (*(*this).Parent).x;
			if ((*(*(*this).Parent).Parent).Left == (*this).Parent) rightLim = (*(*(*this).Parent).Parent).x;
			else rightLim = pLeft.first - leftLim;
		}
		points arcPoints;

		//	Puts an amount of points(according to BEACH_LINE_PRECISION) that form an arc of the Site into the vector.
		//	Point's (x,y) gets from parabola equation.
		for (int i = 0; i < BEACH_LINE_PRECISION ; i++)
		{
			arcPoints.push_back(point(rightLim + double(i) / BEACH_LINE_PRECISION * (leftLim - rightLim),
				(1. / (2 * pLeft.second - y)) *
				(rightLim + double(i) / BEACH_LINE_PRECISION * (leftLim - rightLim) - pLeft.first) *
				(rightLim + double(i) / BEACH_LINE_PRECISION * (leftLim - rightLim) - pLeft.first) +
				(pLeft.second + y) / 2.));
		}
		return arcPoints;
	}
}

Node * Node::opposite()
{
	if ((*this).Parent == nullptr) return nullptr;
	if (this == (*(*this).Parent).Left) return (*(*this).Parent).Right;
	else return (*(*this).Parent).Left;
}
