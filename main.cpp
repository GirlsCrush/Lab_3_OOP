#include <iostream>
#include "BST.h"
#ifndef point
#define point pair<double, double>
#define points vector<point>
#endif

using namespace std;

int main()
{
	points inputPoints = { {1., 0.}, {1., 2.}, {2., 1.} };
	BST bst(inputPoints);
	bst.drawDiagram();
	system("pause");
	return 0;
}
