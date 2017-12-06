#include <iostream>
#include "BST.h"
#include <algorithm>
#include <time.h>
#ifndef point
#define point pair<double, double>
#define points vector<point>
#endif
#define POINT_SIZE 0.1
#define PARABOLA_SIZE 0.025
#define POINTS_NUMBER 3
using namespace std;

void drawVor();
void display(void);
void reshape(int, int);
void onEF();

points BL;
points SITES;
vector<Edge> DIAGR;
double directrix;

points inputPoints;
vector<Edge> finishDiagram;
BST bst;

int main(int argc, char **argv)
{
	/*inputPoints; *//*= { { 0.1, 0.04 },{ 0.15, 0.21 },{ 0.2, 0.13 } };*/
	srand(time(NULL));

	for (int i = 0; i < POINTS_NUMBER; i++)
	{
		inputPoints.push_back(point(10 * ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX), 10* ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX)));
	}

	
	bst.init(inputPoints);
	

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(600, 600); // Set the width and height of the window
	glutInitWindowPosition(750, 100); // Set the position of the window
	glutCreateWindow("Your first OpenGL Window"); // Set the title for the window
	/*bst.updateDiagram();*/
		

		glutIdleFunc(onEF);
		glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
		glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
		glutMainLoop(); // Enter GLUT's main loop
		
	

		
	system("pause");
	return 0;
}


void drawVor()
{

	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red
	for (int i = 0; i < SITES.size(); i++)
	{
		glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f(SITES[i].first - POINT_SIZE, SITES[i].second - POINT_SIZE);
		glVertex2f(SITES[i].first + POINT_SIZE, SITES[i].second - POINT_SIZE);
		glVertex2f(SITES[i].first + POINT_SIZE, SITES[i].second + POINT_SIZE);
		glVertex2f(SITES[i].first - POINT_SIZE, SITES[i].second + POINT_SIZE);
		glEnd();
	}   //**/

	for (int i = 0; i < BL.size(); i++)
	{
		glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f(BL[i].first - PARABOLA_SIZE, BL[i].second - PARABOLA_SIZE);
		glVertex2f(BL[i].first + PARABOLA_SIZE, BL[i].second - PARABOLA_SIZE);
		glVertex2f(BL[i].first + PARABOLA_SIZE, BL[i].second + PARABOLA_SIZE);
		glVertex2f(BL[i].first - PARABOLA_SIZE, BL[i].second + PARABOLA_SIZE);
		glEnd();
	}   //**/

		//**
	for (int i = 0; i < DIAGR.size(); i++)
	{
		/**   This cycle builds the Dilone triangulation
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->left->x/w,  -1+2*(*i)->left->y/w);
		glVertex2f( -1+2*(*i)->right->x/w, -1+2*(*i)->right->y/w);
		glEnd();
		**/ //  <<-----------------------------------------------------------------------------
		//**
		glBegin(GL_LINES);
		glVertex2f(DIAGR[i].start.first, DIAGR[i].start.second);
		glVertex2f(DIAGR[i].end.first, DIAGR[i].end.second);
		glEnd();
		//**/

	}
	// Draws Directix:
	glBegin(GL_LINES);
	glVertex2f(-ORTO, directrix);
	glVertex2f(ORTO, directrix);
	glEnd();
	
}

void onEF()
{
	system("pause");
	if (bst)
	{
		directrix = bst.updateDiagram();
		DIAGR = bst.getEdges();
		BL = bst.getBeachLine();
		SITES = bst.getAddedPoints();
	
	}
	else 
	{
		bst.updateIndent(directrix);
		DIAGR = bst.getEdges();
		BL = bst.getBeachLine();
		SITES = bst.getAddedPoints();
	}
	//system("pause");
	glutPostRedisplay();
}

void reshape(int width, int height)
{

	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
					  ///gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glOrtho(-ORTO, ORTO, -ORTO, ORTO, -1, 10);
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void display(void)
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(0.0f, 0.0f, -5.0f);

	drawVor();
	glutSwapBuffers();
	glFlush();
}


