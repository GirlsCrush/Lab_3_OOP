#include "BST.h"
#define BEACH_LINE_PRECISION 1000.
#define BOTTOM_INDENT 1.
#define SIDE_INTERVAL 20.
#define NULL_NEIGHBOR nullptr
#define EPSILON 0.000001
#define dist(p1, p2) sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second))

void BST::addSite(Event &siteEvent)
{
	point site = siteEvent.eventPoint;
	if (!root)
	{
		root = new Node(site, nullptr, *diagram);
		return;
	}
	Node *upSite = findArc(site.first, root);
	vector<Node*> neighbors = findNieghbors(upSite);
	unsigned int newEdge = diagram.push_Edge((*upSite).pLeft, site);
	if ((*upSite).Parent == nullptr)
	{
		(*upSite).Parent = new Node((*upSite).pLeft, nullptr, *diagram, newEdge);
		root = (*upSite).Parent;
		(*(*upSite).Parent).Left = upSite;

	}
	else
	{
		if ((*(*upSite).Parent).Left == upSite)
		{
			(*(*upSite).Parent).Left = new Node((*upSite).pLeft, (*upSite).Parent, *diagram, newEdge);
			(*(*(*upSite).Parent).Left).Left = upSite;
			(*upSite).Parent = (*(*upSite).Parent).Left;
			(*upSite).edge = newEdge;
		}
		else
		{
			(*(*upSite).Parent).Right = new Node((*upSite).pLeft, (*upSite).Parent, *diagram, newEdge);
			(*(*(*upSite).Parent).Right).Left = upSite;
			(*upSite).Parent = (*(*upSite).Parent).Right;
		}
	}
	(*(*upSite).Parent).pRight = site;
	(*(*upSite).Parent).Right = new Node(site, (*(*upSite).Parent).Left, *diagram, newEdge);
	(*(*(*upSite).Parent).Right).Parent = (*upSite).Parent;
	(*(*(*upSite).Parent).Right).pRight = (*upSite).pLeft;
	(*(*(*upSite).Parent).Right).Left = new Node(site, (*(*(*upSite).Parent).Left).Right, *diagram, newEdge);
	(*(*(*(*upSite).Parent).Right).Left).Parent = (*(*upSite).Parent).Right;
	(*(*(*upSite).Parent).Right).Right = new Node((*upSite).pLeft, (*(*(*upSite).Parent).Left).Right, *diagram, newEdge);
	(*(*(*(*upSite).Parent).Right).Right).Parent = (*(*upSite).Parent).Right;
	if (neighbors[0] != NULL_NEIGHBOR && neighbors[1] != NULL_NEIGHBOR && (*neighbors[0]).pLeft == (*neighbors[1]).pLeft)
	{
		point neighbor = (*neighbors[0]).pLeft;
		double a1 = (site.second - (*upSite).pLeft.second) / (site.first - (*upSite).pLeft.first);
		if ((*upSite).x < site.first)
		{
			if (neighbor.second < a1 * (neighbor.first - (*upSite).pLeft.first) + (*upSite).pLeft.second)
				neighbors[1] = NULL_NEIGHBOR;
			else
				neighbors[0] = NULL_NEIGHBOR;
		}
		else
		{
			if (neighbor.second < a1 * (neighbor.first - (*upSite).pLeft.first) + (*upSite).pLeft.second)
				neighbors[0] = NULL_NEIGHBOR;
			else
				neighbors[1] = NULL_NEIGHBOR;
		}
	}
	if (neighbors[0] != NULL_NEIGHBOR) addCircleEvent((*(*(*upSite).Parent).Right).Left, upSite, neighbors[0]);
	if (neighbors[1] != NULL_NEIGHBOR) addCircleEvent((*(*(*upSite).Parent).Right).Left, (*(*(*upSite).Parent).Right).Right, neighbors[1]);
}

void BST::handleCircleEvent(Event &circleEvent)
{
	//Node *dis = findDisappearArc(circleEvent.circleCenter.first, (*circleEvent.disNode).pLeft);
	Node *dis = circleEvent.disNode;
	Node *tmp = findLeftNeighbor(dis);
	Node *up;
	Node *low;
	bool upIsLeft;
	//if (tmp == NULL_NEIGHBOR) cout << "NULL";
	if ((*tmp).pLeft == (*circleEvent.upperNode).pLeft)
	{
		up = tmp;
		//if (findRightNeighbor(dis) == NULL_NEIGHBOR) cout << "NULL RIGHT";
		low = findRightNeighbor(dis);
		upIsLeft = true;
	}
	else
	{
		//if (findRightNeighbor(dis) == NULL_NEIGHBOR) cout << "NULL RIGHT";
		up = findRightNeighbor(dis);
		low = tmp;
		upIsLeft = false;
	}
	Node *opposite = (*dis).opposite();

		if ((*(*(*dis).Parent).Parent).Left == (*dis).Parent) (*(*(*dis).Parent).Parent).Left = opposite;
	else (*(*(*dis).Parent).Parent).Right = opposite;
	tmp = up;
	if (upIsLeft)
	{
		while ((*tmp).Parent != nullptr)
		{
			tmp = (*tmp).Parent;
			if ((*tmp).pLeft == (*up).pLeft && (*tmp).pRight == (*dis).pLeft)
			{
				(*tmp).pRight = (*low).pLeft;
				break;
			}

		}
	}
	else
	{
		while ((*tmp).Parent != nullptr)
		{
			tmp = (*tmp).Parent;
			if ((*tmp).pLeft == (*dis).pLeft && (*tmp).pRight == (*up).pLeft)
			{
				(*tmp).pLeft = (*low).pLeft;
				break;
			}

		}
	}

	unsigned int newEdge = diagram.push_Edge((*up).pLeft, (*low).pLeft);
	diagram[newEdge].start = point((*tmp).x, (1 / (2 * ((*up).pLeft.second - circleEvent.eventPoint.second))) * ((*tmp).x - ((*up).pLeft.first)) * ((*tmp).x - ((*up).pLeft.first)) + ((*up).pLeft.second + circleEvent.eventPoint.second) / 2);
	diagram[newEdge].end = diagram[newEdge].start;
	(*tmp).edge = newEdge;
	(*opposite).Parent = (*(*dis).Parent).Parent;
	/*if((*(*up).Parent).Left == up) (*(*up).Parent).pRight = (*low).pLeft;
	else
	{
		(*(*up).Parent).pLeft = (*low).pLeft;
	}
	(*(*up).Parent).edge = newEdge;*/
	delete (*dis).Parent;
	delete dis;

	/*vector<Node*> neighbors = findNieghbors(up);
	Node *neigh = NULL_NEIGHBOR;
	if (neighbors[0] != NULL_NEIGHBOR && neighbors[0] == low) neighbors[0] = NULL_NEIGHBOR;
	if (neighbors[1] != NULL_NEIGHBOR && neighbors[1] == low) neighbors[0] = NULL_NEIGHBOR;
	for (int i = 0; i < 2; i++)
	{
		if (neighbors[i] != NULL_NEIGHBOR)
		{
			neigh = neighbors[i];
			break;
		}
	}
	if (neigh != NULL_NEIGHBOR)
	{
		point neighbor = (*neigh).pLeft;
		double a1 = ((*low).pLeft.second - (*up).pLeft.second) / ((*low).pLeft.first - (*up).pLeft.first);
		if (neighbor.second > a1 * (neighbor.first - (*up).pLeft.first) + (*up).pLeft.second) neigh = NULL_NEIGHBOR;
		if (neigh != NULL_NEIGHBOR) addCircleEvent(low, up, neigh);
	}*/
}

BST::BST(points &input): events(input)
{
}

vector<Edge> BST::getEdges()
{
	return diagram.getEdges();
}

points BST::getBeachLine()
{
	return beachLine;
}

points BST::getAddedPoints()
{
	return events.getAddedPoints();
}

double BST::updateDiagram()
{
	Event tmp = events.pop();
	update(tmp.eventPoint.second);
	if (tmp) addSite(tmp);
	else 
		if(tmp.circleCenter != tmp.eventPoint) handleCircleEvent(tmp);
		else return tmp.eventPoint.second;
	beachLine.clear();
	update(tmp.eventPoint.second);
	return tmp.eventPoint.second;
}

void BST::updateIndent(double & y)
{
	beachLine.clear();
	y -= BOTTOM_INDENT;
	update(y);
}

void BST::update(double y)
{
	update(root, y);
}

BST::operator bool()
{
	return !events.empty();
}

void BST::init(points &p)
{
	events.init(p);
}

void BST::addCircleEvent(Node* node1, Node* node2, Node* node3)
{
	if (node1 == nullptr || node2 == nullptr || node3 == nullptr) cout << "addCircle\n\n";
	point p1 = (*node1).pLeft, p2 = (*node2).pLeft, p3 = (*node3).pLeft;
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
	events.push(point(x, y1), point(x, y), node1, node2, node3);
}

Node * BST::findArc(double &siteX, Node *node)
{
	if ((*node)) return node;
	if (siteX < (*node).x) return findArc(siteX, (*node).Left);
	return findArc(siteX, (*node).Right);
}

Node * BST::findLeftNeighbor(Node *node)
{
	Node * tmp = node;
	while ((*(*tmp).Parent).Left == tmp)
	{
		tmp = (*tmp).Parent;
		if ((*tmp).Parent == nullptr) return NULL_NEIGHBOR;
	}
	tmp = (*(*tmp).Parent).Left;
	while (!(*tmp))
	{
		tmp = (*tmp).Right;
	}
	return tmp;
}

Node * BST::findLeftNeighbor(double &siteX, Node * node)
{
	if ((*node)) return node;
	if (siteX <= (*node).x) return findLeftNeighbor(siteX, (*node).Left);
	return findLeftNeighbor(siteX, (*node).Right);
}


Node * BST::findRightNeighbor(Node *node)
{
	Node * tmp = node;
	while ((*(*tmp).Parent).Right == tmp)
	{
		tmp = (*tmp).Parent;
		if ((*tmp).Parent == nullptr) return NULL_NEIGHBOR;
	}
	tmp = (*(*tmp).Parent).Right;
	while (!(*tmp))
	{
		tmp = (*tmp).Left;
	}
	return tmp;
}

Node * BST::findRightNeighbor(double &siteX, Node * node)
{
	if ((*node)) return node;
	if (siteX >= (*node).x) return findRightNeighbor(siteX, (*node).Right);
	return findRightNeighbor(siteX, (*node).Left);
}

Node * BST::findDisappearArc(double &x, point &dis)
{
	vector<Node*> acc;
	vector<Node*> tmp;
	findDisappearArc(x, root, acc);
	for (int i = 0; i < acc.size(); i++)
	{
		if ((*acc[i]).pLeft == dis) tmp.push_back(acc[i]);
	}
	return acc[0];
}

void BST::findDisappearArc(double &x, Node *tmp, vector<Node*> &acc)
{
	if ((*tmp)) return;
	if (abs((*tmp).x - x) < EPSILON)
	{
		Node *tmp1 = tmp;
		while (!(*tmp1))
		{
			tmp1 = (*tmp1).Left;
		}
		acc.push_back(tmp1);
		tmp1 = tmp;
		while (!(*tmp1))
		{
			tmp1 = (*tmp1).Right;
		}
		acc.push_back(tmp1);
	}
	findDisappearArc(x, (*tmp).Left, acc);
	findDisappearArc(x, (*tmp).Right, acc);

}

vector<Node*> BST::findNieghbors(Node * center)
{
	vector<Node*> neigh;
	if ((*center).Parent == nullptr)
	{
		neigh.push_back(NULL_NEIGHBOR);
		neigh.push_back(NULL_NEIGHBOR);
	}
	else
	{
		neigh.push_back(findLeftNeighbor(center));
		neigh.push_back(findRightNeighbor(center));
	}
	/*if (neigh[0] == center) neigh[0] = NULL_NEIGHBOR;
	if (neigh[1] == center) neigh[1] = NULL_NEIGHBOR;*/
	return neigh;
}

void BST::update(Node *node, double &y)
{
	if (node == nullptr) return;
		points arc = (*node)(y);
	for (int i = 0; i < arc.size(); i++) beachLine.emplace_back(arc[i]);
	if (!(*node))
	{
		update((*node).Left, y);
		update((*node).Right, y);
	}
}

vector<point> Node::operator()(double & y)
{
	if (!(*this))
	{
		if (!(((*this).pLeft.second - y) == 0 || ((*this).pRight.second - y) == 0))
		{
			point lower = (pLeft.second < pRight.second ? pLeft : pRight);
			point higher = (pLeft.second > pRight.second ? pLeft : pRight);
			double a1 = (pLeft.first - pRight.first) / (pRight.second - pLeft.second);
			double a2 = (pLeft.first + pRight.first) / 2;
			double a3 = (pLeft.second + pRight.second) / 2;
			double b1 = 1 / (2 * (lower.second - y));
			double b2 = (lower.second + y) / 2;
			double discr = (2 * b1 * lower.first + a1) * (2 * b1 * lower.first + a1) - 4 * b1 * (b1 * lower.first * lower.first + b2 + a1 * a2 - a3);
			double x_1 = ((2 * b1 * lower.first + a1) - sqrt(discr)) / (2 * b1);
			double x_2 = ((2 * b1 * lower.first + a1) + sqrt(discr)) / (2 * b1);
			
			
			if (pLeft.first == lower.first)
			{
				x = (x_1 > lower.first ? x_1 : x_2);
				getEdge().end = point(x, a1 * (x - a2) + a3);
			}
			else
			{
				x = (x_1 > lower.first ? x_2 : x_1);
				getEdge().start = point(x, a1 * (x - a2) + a3);
			}
			return points();
		}
		if (((*this).pLeft.second - y) == 0)
		{
			double a_2 = 1 / (2 * (pRight.second - y));
			double b_2 = (pRight.second + y) / 2;
			x = (*this).pLeft.first;
			getEdge().start = point(x, a_2 * (x - pRight.first) * (x - pRight.first) + b_2);
			getEdge().end = getEdge().start;
			return points();
		}
		if (((*this).pRight.second - y) == 0)
		{
			double a_1 = 1 / (2 * (pLeft.second - y));
			double b_1 = (pLeft.second + y) / 2;
			x = (*this).pRight.first;
			getEdge().start = point(x, a_1 * (x - pLeft.first) * (x - pLeft.first) + b_1);
			getEdge().end = getEdge().start;
			return points();
		}
	}
	else
	{
		if(pLeft.second - y == 0 || (*this).Parent == nullptr) return points();
		double leftLim;
		double rightLim;

		if (this == (*(*this).Parent).Left)
		{
			rightLim = (*(*this).Parent).x;
			Node *tmp = (*this).Parent;
			leftLim = rightLim - SIDE_INTERVAL;
			while ((*tmp).Parent != nullptr)
			{
				if ((*(*tmp).Parent).pRight == pLeft)
				{
					leftLim = (*(*tmp).Parent).x;
					break;
				}
				tmp = (*tmp).Parent;
			}
		}
		else
		{
			leftLim = (*(*this).Parent).x;
			Node *tmp = (*this).Parent;
			rightLim = leftLim + SIDE_INTERVAL;
			while ((*tmp).Parent != nullptr)
			{
				if ((*(*tmp).Parent).Left == tmp)
				{
					rightLim = (*(*tmp).Parent).x;
					break;
				}
				tmp = (*tmp).Parent;
			}
		}
		
		points arcPoints;

		//	Puts an amount of points(according to BEACH_LINE_PRECISION) that form an arc of the Site into the vector.
		//	Point's (x,y) gets from parabola equation.
		for (int i = 0; i < BEACH_LINE_PRECISION ; i++)
		{
			arcPoints.push_back(point(leftLim + double(i) / BEACH_LINE_PRECISION * (rightLim - leftLim),
				(1. / (2 * (pLeft.second - y))) *
				(leftLim + double(i) / BEACH_LINE_PRECISION * (rightLim - leftLim) - pLeft.first) *
				(leftLim + double(i) / BEACH_LINE_PRECISION * (rightLim - leftLim) - pLeft.first) +
				(pLeft.second + y) / 2.));
		}
		return arcPoints;
	}
}
