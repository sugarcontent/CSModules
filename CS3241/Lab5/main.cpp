#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

/* Include header files depending on platform */
#ifdef _WIN32
#include "glut.h"
#define M_PI 3.14159
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#endif

using namespace std;

// You may add more functions here if you like
// ========================================================================
void drawBaseWall()
{
	glBegin(GL_QUADS);
	glTexCoord2d(-2.5, -4); glVertex3f(-2.5, 0, -4);
	glTexCoord2d(2.5, -4); glVertex3f(2.5, 0, -4);
	glTexCoord2d(2.5, -4); glVertex3f(2.5, 2.5, -4);
	glTexCoord2d(-2.5, -4); glVertex3f(-2.5, 2.5, -4);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(-2.5, 0.0); glVertex3f(-2.5, 0, 0);
	glTexCoord2d(2.5, 0.0); glVertex3f(2.5, 0, 0);
	glTexCoord2d(2.5, 0.0); glVertex3f(2.5, 2.5, 0);
	glTexCoord2d(-2.5, 0.0); glVertex3f(-2.5, 2.5, 0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(2.5, 0.0); glVertex3f(2.5, 0, 0);
	glTexCoord2d(3.5, -2.0); glVertex3f(3.5, 0, -2);
	glTexCoord2d(3.5, -2.0); glVertex3f(3.5, 2.5, -2);
	glTexCoord2d(2.5, 0.0); glVertex3f(2.5, 2.5, 0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(-2.5, 0.0); glVertex3f(-2.5, 0, 0);
	glTexCoord2d(-3.5, -2.0); glVertex3f(-3.5, 0, -2);
	glTexCoord2d(-3.5, -2.0); glVertex3f(-3.5, 2.5, -2);
	glTexCoord2d(-2.5, 0.0); glVertex3f(-2.5, 2.5, 0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(-3.5, -2.0); glVertex3f(-3.5, 0, -2);
	glTexCoord2d(-2.5, -4.0); glVertex3f(-2.5, 0, -4);
	glTexCoord2d(-2.5, -4.0); glVertex3f(-2.5, 2.5, -4);
	glTexCoord2d(-3.5, -2.0); glVertex3f(-3.5, 2.5, -2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(3.5, -2.0); glVertex3f(3.5, 0, -2);
	glTexCoord2d(2.5, -4.0); glVertex3f(2.5, 0, -4);
	glTexCoord2d(2.5, -4.0); glVertex3f(2.5, 2.5, -4);
	glTexCoord2d(3.5, -2.0); glVertex3f(3.5, 2.5, -2);
	glEnd();
}

void drawGrass()
{
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-5, -0.001, -5);
	glTexCoord2d(1, 0);	glVertex3f(5, -0.001, -5);
	glTexCoord2d(1, 1); glVertex3f(5, -0.001, 5);
	glTexCoord2d(0, 1); glVertex3f(-5, -0.001, 5);
	glEnd();
}

void draw1stFloor()
{
	glBegin(GL_POLYGON);

	glTexCoord2d(-2.5, 0);
	glVertex3f(-2.5, 2.5, 0);

	glTexCoord2d(-3.5, -2);
	glVertex3f(-3.5, 2.5, -2);

	glTexCoord2d(-2.5, -4);
	glVertex3f(-2.5, 2.5, -4);

	glTexCoord2d(2.5, -4);
	glVertex3f(2.5, 2.5, -4);

	glTexCoord2d(3.5, -2);
	glVertex3f(3.5, 2.5, -2);

	glTexCoord2d(2.5, 0);
	glVertex3f(2.5, 2.5, 0);

	glEnd();
}

void drawCylinder(double r, double h)
{
	int n = 30;

	for (int i = 0; i<n; i++) {
		glBegin(GL_POLYGON);
		glNormal3d(sin(2.0*M_PI*(i + 0.5) / 30.0), cos(2.0*M_PI*(i + 0.5) / 30.0), 0);
		glTexCoord2d(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0));
		glVertex3f(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0), 0);

		glTexCoord2d(r*sin(2.0*M_PI*(i + 1) / 30.0), r*cos(2.0*M_PI*(i + 1) / 30.0));
		glVertex3f(r*sin(2.0*M_PI*(i + 1) / 30.0), r*cos(2.0*M_PI*(i + 1) / 30.0), 0);

		glTexCoord2d(r*sin(2.0*M_PI*(i + 1) / 30.0), r*cos(2.0*M_PI*(i + 1) / 30.0));
		glVertex3f(r*sin(2.0*M_PI*(i + 1) / 30.0), r*cos(2.0*M_PI*(i + 1) / 30.0), h);

		glTexCoord2d(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0));
		glVertex3f(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0), h);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glNormal3d(0, 0, -1);

	for (int i = 0; i < n; i++) {
		glVertex3f(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0), 0);
	}

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0, 0, 1);

	for (int i = 0; i < n; i++) {
		glVertex3f(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0), h);
	}
	glEnd();

}

void draw1stPillars()
{
	glPushMatrix();
	glTranslatef(-2.5, 0, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0, -4);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 0, -4);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 0, -2);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 0, -2);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 2.5);
	glPopMatrix();
}

void draw2ndFloor() {
	float wth = 1.5;
	float ht = 9.5;

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-wth, 2.5, -3.5);
	glTexCoord2d(1, 1); glVertex3f(wth, 2.5, -3.5);
	glTexCoord2d(1, 0); glVertex3f(wth, ht, -3.5);
	glTexCoord2d(0, 1); glVertex3f(-wth, ht, -3.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-wth, 2.5, -0.5);
	glTexCoord2d(1, 1);  glVertex3f(wth, 2.5, -0.5);
	glTexCoord2d(1, 0); glVertex3f(wth, ht, -0.5);
	glTexCoord2d(0, 1); glVertex3f(-wth, ht, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	 glTexCoord2d(1, 0); glVertex3f(wth, 2.5, -0.5);
	 glTexCoord2d(1, 1); glVertex3f(wth + 1, 2.5, -2.0);
	 glTexCoord2d(0, 1); glVertex3f(wth + 1, ht, -2.0);
	 glTexCoord2d(0, 0); glVertex3f(wth, ht, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(wth + 1, 2.5, -2.0);
	 glTexCoord2d(0, 1); glVertex3f(wth + 1, ht, -2.0);
	glTexCoord2d(0, 0); glVertex3f(wth, ht, -3.5);
	glTexCoord2d(1, 1);  glVertex3f(wth, 2.5, -3.5);
	glEnd();


	glBegin(GL_QUADS);
	 glTexCoord2d(1, 0);  glVertex3f(-(wth + 1), 2.5, -2.0);
	  glTexCoord2d(0, 1); glVertex3f(-(wth + 1), ht, -2.0);
	 glTexCoord2d(0, 0); glVertex3f(-wth, ht, -3.5);
	 glTexCoord2d(1, 1); glVertex3f(-wth, 2.5, -3.5);
	glEnd();
	
	glBegin(GL_QUADS);
	 glTexCoord2d(1, 1); glVertex3f(-(wth + 1), 2.5, -2.0);
	 glTexCoord2d(0, 0); glVertex3f(-wth, 2.5, -0.5);
	 glTexCoord2d(0, 1);  glVertex3f(-wth, ht, -0.5);
	glTexCoord2d(1, 0); glVertex3f(-(wth + 1), ht, -2.0);
	glEnd();

	glBegin(GL_POLYGON);

	glTexCoord2d(-2.5, 0);
	glVertex3f(-wth, 9.501, -0.5);

	glTexCoord2d(-3.5, -2);
	glVertex3f(-(wth+1), 9.501, -2);

	glTexCoord2d(-2.5, -4);
	glVertex3f(-wth, 9.501, -3.5);

	glTexCoord2d(2.5, -4);
	glVertex3f(wth, 9.501, -3.5);

	glTexCoord2d(3.5, -2);
	glVertex3f(wth+1, 9.501, -2);

	glTexCoord2d(2.5, 0);
	glVertex3f(wth, 9.501, -0.5);

	glEnd();

}

void draw3rdFloor() {
	float wth = 1.25;
	float prevHt = 9.501;
	float ht = prevHt + 0.5;
	

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-wth, prevHt, -3.5);
	glTexCoord2d(1, 1); glVertex3f(wth, prevHt, -3.5);
	glTexCoord2d(1, 0); glVertex3f(wth, ht, -3.5);
	glTexCoord2d(0, 1); glVertex3f(-wth, ht, -3.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-wth, prevHt, -0.5);
	glTexCoord2d(1, 1);  glVertex3f(wth, prevHt, -0.5);
	glTexCoord2d(1, 0); glVertex3f(wth, ht, -0.5);
	glTexCoord2d(0, 1); glVertex3f(-wth, ht, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(wth, prevHt, -0.5);
	glTexCoord2d(1, 1); glVertex3f(wth + 1, prevHt, -2.0);
	glTexCoord2d(0, 1); glVertex3f(wth + 1, ht, -2.0);
	glTexCoord2d(0, 0); glVertex3f(wth, ht, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(wth + 1, prevHt, -2.0);
	glTexCoord2d(0, 1); glVertex3f(wth + 1, ht, -2.0);
	glTexCoord2d(0, 0); glVertex3f(wth, ht, -3.5);
	glTexCoord2d(1, 1);  glVertex3f(wth, prevHt, -3.5);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);  glVertex3f(-(wth + 1), prevHt, - 2.0);
	glTexCoord2d(0, 1); glVertex3f(-(wth + 1), ht, -2.0);
	glTexCoord2d(0, 0); glVertex3f(-wth, ht, -3.5);
	glTexCoord2d(1, 1); glVertex3f(-wth, prevHt, -3.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(1, 1); glVertex3f(-(wth + 1), prevHt, -2.0);
	glTexCoord2d(0, 0); glVertex3f(-wth, prevHt, -0.5);
	glTexCoord2d(0, 1);  glVertex3f(-wth, ht, -0.5);
	glTexCoord2d(1, 0); glVertex3f(-(wth + 1), ht, -2.0);
	glEnd();

}

void draw2ndPillars()
{
	float wth = 1.5;
	float ht = 9.5;

	glPushMatrix();
	glTranslatef(-wth, 0, -0.5);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, ht);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(wth, 0, -0.5);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, ht);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(wth, 0, -3.5);
	glRotatef(-90, 1, 0 , 0);
	drawCylinder(0.2, ht);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-wth, 0, -3.5);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, ht);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(wth + 1, 0, -2);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, ht);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(wth + 1), 0, -2);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, ht);
	glPopMatrix();
}

void drawRoof(double r, double h)
{

	int n = 30;

	glPushMatrix();
	glTranslatef(0, 10, -2);
	glRotatef(-90, 1, 0, 0);

	for (int i = 0; i < n; i++) {
		glNormal3d(sin(2.0*M_PI*(i + 0.5) / 30.0), cos(2.0*M_PI*(i + 0.5) / 30.0), h / 2);
		glBegin(GL_POLYGON);
		glTexCoord2d(1, 0);
		glVertex3f(r*sin(2.0*M_PI*i / 30.0), r*cos(2.0*M_PI*i / 30.0), 0);
		glTexCoord2d(0, 1);
		glVertex3f(r*sin(2.0*M_PI*(i + 1) / 30.0), r*cos(2.0*M_PI*(i + 1) / 30.0), 0);
		glVertex3f(0, 0, h);
		glEnd();
	}
	glPopMatrix();
}

void drawWindmillBlade()
{
	glBegin(GL_POLYGON);
	
	glTexCoord2d(0, -0.5);
	glVertex3f(0, -0.5, 0.1);

	glTexCoord2d(0, 0.5);
	glVertex3f(0, 0.5, 0.1);

	glTexCoord2d(-5, 1);
	glVertex3f(-5, 1, 0.1);

	glTexCoord2d(-5, -1);
	glVertex3f(-5, -1, 0.1);

	glEnd();
}

void drawMailCtr(double r)
{
	int n = 20;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			glBegin(GL_POLYGON);
			// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));

			glTexCoord3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
			glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

			glTexCoord3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
			glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

			glTexCoord3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
			glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

			glTexCoord3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
			glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
			glEnd();
		}
}

}
// ========================================================================

void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -5:5
	//y: >= 0
	//z: -5:5

	// Your main drawing code goes here
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[43]);

	drawBaseWall();
	draw1stFloor();
	draw2ndFloor();
	draw3rdFloor();

	glBindTexture(GL_TEXTURE_2D, texSet[19]);
	drawMailCtr(1);
	
	glBindTexture(GL_TEXTURE_2D, texSet[16]);
	drawRoof(2.2, 1.5);

	glBindTexture(GL_TEXTURE_2D, texSet[11]);
	draw1stPillars();
	draw2ndPillars();

	glBindTexture(GL_TEXTURE_2D, texSet[42]);

	drawGrass();

	glDisable(GL_TEXTURE_2D);
	// =========================================
}



// ********** You do not need to edit any code beyond this point **********

// The following code supports loading textures from disk
// ========================================================================
GLuint texSet[45];
GLuint loadMyTextures(char *filename)
{
	GLuint myTexture;
	FILE * file;
	unsigned char *tex, *tex2;

	// texture data
	int width = 256;
	int height = 256;

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	file = fopen(filename, "rb");

	if (file == NULL)
		cout << "Error! Missing texture!\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}
// ========================================================================

// The following code is used to support rotation of the scene with your mouse
// ========================================================================
bool isDraggingLeft = false;
bool isDraggingRight = false;
int prevX = 0, prevY = 0;
int curX = 0, curY = 0;
float angle1 = M_PI, angle2 = -1;	// angles are in radians
float dist = 12.0;
float lookY = 5;
float aspectRatio = 1.0;

void LMBDragged(float dx, float dy) {
	angle1 -= ((float)dx) / 150.0;
	angle2 += ((float)dy) / 150.0;

	if (angle1 < 0)	angle1 += 2 * M_PI;
	else if (angle1 > 2 * M_PI) angle1 -= 2 * M_PI;
	if (angle2 < 0)	angle2 += 2 * M_PI;
	else if (angle2 > 2 * M_PI) angle2 -= 2 * M_PI;
}

void RMBDragged(float dx, float dy) {
	dist += ((float)dx) / 100.0;
	lookY += ((float)dy) / 50.0;
}

void computeCameraPosition() {
	float camX = dist * sin(angle1) * sin(angle2);
	float camY = dist * cos(angle2);
	float camZ = dist * cos(angle1) * sin(angle2);

	float upVectorY = 1.0;
	if (angle2 >= 0 && angle2 < M_PI) {
		upVectorY = -1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	gluLookAt(camX, camY + lookY, camZ, 0, lookY, 0, 0, upVectorY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetCamera() {
	angle1 = M_PI;
	angle2 = -1;
	lookY = 5;
	dist = 15.0;
}
// ========================================================================


// The following code is the usual stuff you give OpenGL
// ========================================================================

void init(void)
{
	glClearColor(0.73, 0.90, 0.96, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	texSet[0] = loadMyTextures("brick1.bmp");
	texSet[1] = loadMyTextures("brick2.bmp");
	texSet[2] = loadMyTextures("brick3.bmp");
	texSet[3] = loadMyTextures("brick4.bmp");
	texSet[4] = loadMyTextures("door1.bmp");
	texSet[5] = loadMyTextures("door2.bmp");
	texSet[6] = loadMyTextures("flower1.bmp");
	texSet[7] = loadMyTextures("flower2.bmp");
	texSet[8] = loadMyTextures("flower3.bmp");
	texSet[9] = loadMyTextures("grass1.bmp");

	texSet[10] = loadMyTextures("grass2.bmp");
	texSet[11] = loadMyTextures("leaves1.bmp");
	texSet[12] = loadMyTextures("leaves2.bmp");
	texSet[13] = loadMyTextures("roof1.bmp");
	texSet[14] = loadMyTextures("roof2.bmp");
	texSet[15] = loadMyTextures("roof3.bmp");
	texSet[16] = loadMyTextures("roof4.bmp");
	texSet[17] = loadMyTextures("roof5.bmp");
	texSet[18] = loadMyTextures("roof6.bmp");
	texSet[19] = loadMyTextures("stone1.bmp");

	texSet[20] = loadMyTextures("stone2.bmp");
	texSet[21] = loadMyTextures("tile1.bmp");
	texSet[22] = loadMyTextures("tile2.bmp");
	texSet[23] = loadMyTextures("tile3.bmp");
	texSet[24] = loadMyTextures("tile4.bmp");
	texSet[25] = loadMyTextures("tile5.bmp");
	texSet[26] = loadMyTextures("tile6.bmp");
	texSet[27] = loadMyTextures("window1.bmp");
	texSet[28] = loadMyTextures("window2.bmp");
	texSet[29] = loadMyTextures("window3.bmp");

	texSet[30] = loadMyTextures("window4.bmp");
	texSet[31] = loadMyTextures("window5.bmp");
	texSet[32] = loadMyTextures("window6.bmp");
	texSet[33] = loadMyTextures("wood1.bmp");
	texSet[34] = loadMyTextures("wood2.bmp");
	texSet[35] = loadMyTextures("wood3.bmp");
	texSet[36] = loadMyTextures("wood4.bmp");
	texSet[37] = loadMyTextures("wood5.bmp");
	texSet[38] = loadMyTextures("wood6.bmp");
	texSet[39] = loadMyTextures("wood7.bmp");

	texSet[40] = loadMyTextures("custom/custom1.bmp");
	texSet[41] = loadMyTextures("custom/custom2.bmp");
	texSet[42] = loadMyTextures("custom/custom3.bmp");
	texSet[43] = loadMyTextures("custom/custom4.bmp");
	texSet[44] = loadMyTextures("custom/custom5.bmp");

	cout << "Texture loading complete" << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1.0, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspectRatio = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int startTime = glutGet(GLUT_ELAPSED_TIME);
	int counter = 1;

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawMyHouse(texSet);

	int endTime = glutGet(GLUT_ELAPSED_TIME);
	// cout<<"Frame Rate: "<<(float)1000/(endTime-startTime)<<"\n";
	glFlush();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)
{

	if (!isDraggingLeft && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = true;
		isDraggingRight = false;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isDraggingLeft = false;
		prevX = 0;
		prevY = 0;
	}

	if (!isDraggingRight && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = false;
		isDraggingRight = true;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isDraggingRight = false;
		prevX = 0;
		prevY = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		resetCamera();
		computeCameraPosition();
		glutPostRedisplay();
	}

}

void mouseMotion(int x, int y) {
	if (isDraggingLeft) {
		float dx = x - prevX;
		float dy = y - prevY;

		LMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}

	if (isDraggingRight) {
		float dx = x - prevX;
		float dy = y - prevY;

		RMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		dist -= 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 's' || key == 'S') {
		dist += 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 27) {
		exit(0);
	}
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 5\n\n";
	cout << "+++++CONTROLS+++++++\n\n";
	cout << "Left Click and Drag: Rotate camera\n";
	cout << "Right Click and Drag:\n";
	cout << "\tVertical: Change camera elevation\n";
	cout << "\tHorizontal: Zoom in and out\n";
	cout << "Middle Click: Reset camera\n";
	cout << "W: Zoom In\n";
	cout << "S: Zoom Out\n";
	cout << "ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

// ========================================================================

