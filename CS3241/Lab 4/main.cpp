// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include "glut.h"
#define M_PI 3.14159
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#endif

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8

using namespace std;

void drawCircle(float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float cos = cosf(theta);//precalculate the sine and cosine
	float sin = sinf(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
	for (int j = 0; j < num_segments; j++)
	{
		if (j < 100)
			glColor3f(1, 0, 0);
		else if (j < 200)
			glColor3f(1, 0.5, 0);
		else if (j < 300)
			glColor3f(1, 1, 0.0);
		else if (j < 400)
			glColor3f(0, 1, 0);
		else if (j < 500)
			glColor3f(0.184314, 0.309804, 0.184314);
		else if (j < 600)
			glColor3f(0.74902, 0.847059, 0.847059);
		else if (j < 700)
			glColor3f(0, 0, 1);
		else if (j < 800)
			glColor3f(1, 0, 1);
		else if (j < 900)
			glColor3f(0.6, 0.196078, 0.8);
		else if (j < 1000)
			glColor3f(0, 1, 0.498039);

		glVertex2f(x, y);//output vertex 
		//apply the rotation matrix
		t = x;
		x = cos * x - sin * y;
		y = sin * t + cos * y;
	}
	glEnd();
}

void drawStar() {
	glColor3f(0.85, 0.85, 0.1);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(180, 0, 0, 1);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0, 0);
	glVertex2d(10, 20);
	glVertex2d(25, 20);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0, 20);
	glVertex2d(15, 20);
	glVertex2d(25, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(16, 20);
	glVertex2d(9, 20);
	glVertex2d(12.5, 30);
	glEnd();

	glPopMatrix();
}

// Global variables that you can use
struct Point {
	int x, y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;

Point C1_newpt(Point a, Point b){
	Point newPt;
	newPt.x = 2 * b.x - a.x;
	newPt.y = 2 * b.y - a.y;

	return newPt;
}

//Tangent line code
void drawTangent()
{
	glColor3f(0, 0.9, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glVertex2f(95, 5);
	glVertex2f(100, 0);
	glVertex2f(95, -5);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	if (displayControlPoints)
	{
		Point temp;
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i<nPt; i++)
		{
			glColor3f(0, 0, 0);

			if (i % 3 == 1 && i != 1){
				if (C1Continuity){
					temp = C1_newpt(ptList[i - 2], ptList[i - 1]);
					glColor3f(1, 0, 0);
					glVertex2d(temp.x, temp.y);

					glColor3f(0.6, 0.6, 0.6);
					glVertex2d(ptList[i].x, ptList[i].y);
				}
				else
					glVertex2d(ptList[i].x, ptList[i].y);
			}
			else
				glVertex2d(ptList[i].x, ptList[i].y);
		}
		glEnd();
		glPointSize(1);
	}

	if (displayControlLines)
	{
		Point temp;
		glColor3f(0, 1, 0);

		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i<nPt; i++)
		{
			if (i % 3 == 1 && i != 1){
				if (C1Continuity) {
					temp = C1_newpt(ptList[i - 2], ptList[i - 1]);
					glVertex2d(temp.x, temp.y);
				}
				else
					glVertex2d(ptList[i].x, ptList[i].y);
			}
			else
				glVertex2d(ptList[i].x, ptList[i].y);
		}
		glEnd();

	}

	//Bezier Curve Code
	if (C1Continuity){
		Point tempCurr;
		glColor3f(0, 0, 1);
		for (int i = 0; i + 3<nPt; i += 3)
		{
			if (i != 0)
				tempCurr = C1_newpt(ptList[i - 1], ptList[i]);

			if (displayObjects){
				glColor3f(0.5, 0.12, 0.47);
				glLineWidth(10);
			}
			else {
				glLineWidth(1);
			}

			glBegin(GL_LINE_STRIP);
			for (double t = 0; t <= 1; t = t + 1.0 / NLINESEGMENT)
			{
				if (i != 0) {
					double x = pow(1 - t, 3)*ptList[i].x + 3 * pow(1 - t, 2)*t*tempCurr.x + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].x + pow(t, 3)*ptList[i + 3].x;
					double y = pow(1 - t, 3)*ptList[i].y + 3 * pow(1 - t, 2)*t*tempCurr.y + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].y + pow(t, 3)*ptList[i + 3].y;
					glVertex2f(x, y);
				}
				else {
					double x = pow(1 - t, 3)*ptList[i].x + 3 * pow(1 - t, 2)*t*ptList[i + 1].x + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].x + pow(t, 3)*ptList[i + 3].x;
					double y = pow(1 - t, 3)*ptList[i].y + 3 * pow(1 - t, 2)*t*ptList[i + 1].y + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].y + pow(t, 3)*ptList[i + 3].y;
					glVertex2f(x, y);
				}
			}

			glEnd();

			if (displayObjects){
				glPushMatrix();
				glTranslatef(ptList[i].x, ptList[i].y, 0);
				drawStar();
				glPopMatrix();
			}
		}

	}
	else {

		glColor3f(0, 0, 1);
		for (int i = 0; i + 3<nPt; i += 3)
		{
			if (displayObjects){
				glColor3f(0.5, 0.12, 0.47);
				glLineWidth(10);
			}
			else {
				glLineWidth(1);
			}
			glBegin(GL_LINE_STRIP);
			for (double t = 0; t <= 1; t = t + 1.0 / NLINESEGMENT)
			{
				double x = pow(1 - t, 3)*ptList[i].x + 3 * pow(1 - t, 2)*t*ptList[i + 1].x + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].x + pow(t, 3)*ptList[i + 3].x;
				double y = pow(1 - t, 3)*ptList[i].y + 3 * pow(1 - t, 2)*t*ptList[i + 1].y + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].y + pow(t, 3)*ptList[i + 3].y;
				glVertex2f(x, y);
			}
			glEnd();

			if (displayObjects){
				glPushMatrix();
				glTranslatef(ptList[i].x, ptList[i].y, 0);
				drawStar();
				glPopMatrix();
			}
		}
	}

	if (displayObjects || displayTangentVectors) {
		double radian;
		Point tempCurr;
		double cx, cy, x, y;
		for (int i = 0; i + 3 < nPt; i += 3)
		{
			for (double t = 0; t < 1; t = t + 1.0 / NOBJECTONCURVE){
				if (!C1Continuity || (C1Continuity && i == 0)){
					cx = -3 * pow(1 - t, 2)*ptList[i].x + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*ptList[i + 1].x + (6 * (1 - t)*t - 3 * pow(t, 2))*ptList[i + 2].x + 3 * pow(t, 2)*ptList[i + 3].x;
					cy = -3 * pow(1 - t, 2)*ptList[i].y + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*ptList[i + 1].y + (6 * (1 - t)*t - 3 * pow(t, 2))*ptList[i + 2].y + 3 * pow(t, 2)*ptList[i + 3].y;
					x = pow(1 - t, 3)*ptList[i].x + 3 * pow(1 - t, 2)*t*ptList[i + 1].x + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].x + pow(t, 3)*ptList[i + 3].x;
					y = pow(1 - t, 3)*ptList[i].y + 3 * pow(1 - t, 2)*t*ptList[i + 1].y + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].y + pow(t, 3)*ptList[i + 3].y;
				}
				else {
					tempCurr = C1_newpt(ptList[i - 1], ptList[i]);
					cx = -3 * pow(1 - t, 2)*ptList[i].x + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*tempCurr.x + (6 * (1 - t)*t - 3 * pow(t, 2))*ptList[i + 2].x + 3 * pow(t, 2)*ptList[i + 3].x;
					cy = -3 * pow(1 - t, 2)*ptList[i].y + (3 * pow(1 - t, 2) - 6 * (1 - t)*t)*tempCurr.y + (6 * (1 - t)*t - 3 * pow(t, 2))*ptList[i + 2].y + 3 * pow(t, 2)*ptList[i + 3].y;
					x = pow(1 - t, 3)*ptList[i].x + 3 * pow(1 - t, 2)*t*tempCurr.x + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].x + pow(t, 3)*ptList[i + 3].x;
					y = pow(1 - t, 3)*ptList[i].y + 3 * pow(1 - t, 2)*t*tempCurr.y + 3 * (1 - t)*pow(t, 2)*ptList[i + 2].y + pow(t, 3)*ptList[i + 3].y;
				}
				glPushMatrix();
				glTranslatef(x, y, 0);
				if (cx < 0)
					radian = atan(cy / cx) + 3.14159;
				else
					radian = atan(cy / cx);
				glRotatef(atan(cy / cx) * 180 / 3.14, 0, 0, 1);
				if (displayObjects && t != 0 && t != 1.0 / NOBJECTONCURVE)
					drawStar();
				if (displayTangentVectors)
					drawTangent();
				glPopMatrix();
			}
		}
	}

	if (displayObjects && nPt >= 1){

		glPushMatrix();
		glTranslatef(ptList[nPt - 1].x, ptList[nPt - 1].y, 0);
		glRotatef(90, 0, 0, 1);
		drawCircle(50, 1000);
		glPopMatrix();
	}

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void readFile()
{

	std::ifstream file;
	file.open("savefile.txt");
	file >> nPt;

	if (nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for (int i = 0; i<nPt; i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
	file.open("savefile.txt");
	file << nPt << endl;

	for (int i = 0; i<nPt; i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
	case 'R':
		readFile();
		break;

	case 'w':
	case 'W':
		writeFile();
		break;

	case 'T':
	case 't':
		displayTangentVectors = !displayTangentVectors;
		break;

	case 'o':
	case 'O':
		displayObjects = !displayObjects;
		break;

	case 'p':
	case 'P':
		displayControlPoints = !displayControlPoints;
		break;

	case 'L':
	case 'l':
		displayControlLines = !displayControlLines;
		break;

	case 'C':
	case 'c':
		C1Continuity = !C1Continuity;
		break;

	case 'e':
	case 'E':
		// Do something to erase all the control points added
		nPt = 0;

		break;

	case 'u':
	case 'U':
		nPt--;

		break;

	case 'Q':
	case 'q':
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if ((button == MOUSE_LEFT_BUTTON) && (state == GLUT_UP))
	{
		if (nPt == MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x = x;
		ptList[nPt].y = y;
		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 4" << endl << endl;
	cout << "Left mouse click: Add a control point" << endl;
	cout << "Q: Quit" << endl;
	cout << "P: Toggle displaying control points" << endl;
	cout << "L: Toggle displaying control lines" << endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" << endl;
	cout << "T: Toggle displaying tangent vectors" << endl;
	cout << "O: Toggle displaying objects" << endl;
	cout << "R: Read in control points from \"savefile.txt\"" << endl;
	cout << "W: Write control points to \"savefile.txt\"" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CS3241 Assignment 4");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

