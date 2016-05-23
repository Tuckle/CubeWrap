#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void display();
void specialKeys();

double rotate_y = 0;
double rotate_x = 0;
double cubeSide = 0.6, bandDepth = 0.2, bandWidth = 0.3, bandLength = 0.2;
double bx = 0.5, by = 0.5, bz = 0.5;
double elasticityCoef = 0, extraSpace = 0;
bool straightToOrigin = false;//if i can end the wrap straight in the origin point
double nrOfWraps = 0;

//extra variables to use
double cbx, cby, cbz;
double maxBandLength, copyBandLength;

//bandSide fromStart == false if I start from coordinates bx, by, bz
//if toEnd == true then i finish my bandSide until coordinates cbx, cby, cbz
void bandSideFront(bool fromStart = true, bool toEnd = true, double r = 0.5, double g = 0.5, double b = 0.5) {
	///fromStart means we cover all the sides length with the band
	///else we cover only from bx to the end
	///which means we move only the points on the left
	//front grey band
	glBegin(GL_POLYGON);//front
	glColor3f(r, g, b);
	if (!toEnd) {
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide - bandDepth);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
	}
	if (!fromStart) {
		glVertex3f(-bx, by+bandWidth/2, -cubeSide - bandDepth);
		glVertex3f(-bx, by-bandWidth/2, -cubeSide - bandDepth);
	}
	else {
		glVertex3f(-cubeSide, by+bandWidth/2, -cubeSide - bandDepth);
		glVertex3f(-cubeSide, by-bandWidth/2, -cubeSide - bandDepth);
	}
	glEnd();
	glBegin(GL_POLYGON);//back
	if (!toEnd) {
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide);
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
	}
	if (!fromStart) {
		glVertex3f(-bx, by + bandWidth / 2, -cubeSide);
		glVertex3f(-bx, by - bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide);
		glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//right
	if (!toEnd) {
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide);
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//left
	if (!fromStart) {
		glVertex3f(-bx, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-bx, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-bx, by - bandWidth / 2, -cubeSide);
		glVertex3f(-bx, by + bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide);
		glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//top
	if (!toEnd) {
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide);
		glVertex3f(-cbx, by + bandWidth / 2, -cubeSide - bandDepth);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
	}
	if (!fromStart) {
		glVertex3f(-bx, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-bx, by + bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//down
	if (!toEnd) {
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide);
		glVertex3f(-cbx, by - bandWidth / 2, -cubeSide - bandDepth);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
	}
	if (!fromStart) {
		glVertex3f(-bx, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-bx, by - bandWidth / 2, -cubeSide);
	}
	else {
		glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide - bandDepth);
		glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide);
	}
	glEnd();
}
void bandSideRight(bool fromStart = true, bool toEnd = true, double r = 0.5, double g = 0.6, double b = 0.7) {
	glBegin(GL_POLYGON);//front
	glColor3f(r, g, b);
	if (!fromStart) {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -bx);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -bx);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
	}
	glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, cubeSide  + bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//back
	if (!fromStart) {
		glVertex3f(cubeSide, by - bandWidth / 2, -bx);
		glVertex3f(cubeSide, by + bandWidth / 2, -bx);
	}
	else {
		glVertex3f(cubeSide, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide, by + bandWidth / 2, -cubeSide);
	}
	glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//left
	if (!fromStart) {
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -bx);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -bx);
		glVertex3f(cubeSide, by - bandWidth / 2, -bx);
		glVertex3f(cubeSide, by + bandWidth / 2, -bx);
	}
	else {
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide, by + bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//right
	glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//top
	glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
	if (!fromStart) {
		glVertex3f(cubeSide, by + bandWidth / 2, -bx);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -bx);
	}
	else {
		glVertex3f(cubeSide, by + bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by + bandWidth / 2, -cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//bottom
	glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
	if (!fromStart) {
		glVertex3f(cubeSide, by - bandWidth / 2, -bx);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -bx);
	}
	else {
		glVertex3f(cubeSide, by - bandWidth / 2, -cubeSide);
		glVertex3f(cubeSide + bandDepth, by - bandWidth / 2, -cubeSide);
	}
	glEnd();
}
void bandSideBack(bool fromStart = true, bool toEnd = true, double r = 0.6, double g = 0.7, double b = 0.8) {
	glBegin(GL_POLYGON);//front
	glColor3f(r, g, b);
	if (!fromStart) {
		glVertex3f(bx, by - bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(bx, by + bandWidth / 2, cubeSide + bandDepth);
	}
	else {
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
	}
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide + bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//back
	if (!fromStart) {
		glVertex3f(bx, by - bandWidth / 2, cubeSide);
		glVertex3f(bx, by + bandWidth / 2, cubeSide);
	}
	else {
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide);
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide);
	}
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
	glEnd();
	glBegin(GL_POLYGON);//left(viewed from the back)
	if (!fromStart) {
		glVertex3f(bx, by + bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(bx, by - bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(bx, by - bandWidth / 2, cubeSide);
		glVertex3f(bx, by + bandWidth / 2, cubeSide);
	}
	else {
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide);
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//right
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
	glEnd();
	glBegin(GL_POLYGON);//top
	if (!fromStart) {
		glVertex3f(bx, by + bandWidth / 2, cubeSide);
		glVertex3f(bx, by + bandWidth / 2, cubeSide + bandDepth);
	}
	else {
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide);
		glVertex3f(cubeSide, by + bandWidth / 2, cubeSide + bandDepth);
	}
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
	glEnd();
	glBegin(GL_POLYGON);//down
	if (!fromStart) {
		glVertex3f(bx, by - bandWidth / 2, cubeSide);
		glVertex3f(bx, by - bandWidth / 2, cubeSide + bandDepth);
	}
	else {
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide);
		glVertex3f(cubeSide, by - bandWidth / 2, cubeSide + bandDepth);
	}
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide + bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
	glEnd();
}
void bandSideLeft(bool fromStart = true, bool toEnd = true, double r = 0.7, double g = 0.5, double b = 0.8) {
	glBegin(GL_POLYGON);//front
	glColor3f(r, g, b);
	if (!fromStart) {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, bx);
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, bx);
	}
	else {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
	}
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//back
	if (!fromStart) {
		glVertex3f(-cubeSide, by - bandWidth / 2, bx);
		glVertex3f(-cubeSide, by + bandWidth / 2, bx);
	}
	else {
		glVertex3f(-cubeSide, by - bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide, by + bandWidth / 2, cubeSide);
	}
	glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide - bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//left
	if (!fromStart) {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, bx);
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, bx);
		glVertex3f(-cubeSide, by + bandWidth / 2, bx);
		glVertex3f(-cubeSide, by - bandWidth / 2, bx);
	}
	else {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide, by + bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide, by - bandWidth / 2, cubeSide);
	}
	glEnd();
	glBegin(GL_POLYGON);//right
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide - bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//top
	if (!fromStart) {
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, bx);
		glVertex3f(-cubeSide, by + bandWidth / 2, bx);
	}
	else {
		glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide, by + bandWidth / 2, cubeSide);
	}
	glVertex3f(-cubeSide, by + bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide - bandDepth, by + bandWidth / 2, -cubeSide - bandDepth);
	glEnd();
	glBegin(GL_POLYGON);//down
	if (!fromStart) {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, bx);
		glVertex3f(-cubeSide, by - bandWidth / 2, bx);
	}
	else {
		glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, cubeSide);
		glVertex3f(-cubeSide, by - bandWidth / 2, cubeSide);
	}
	glVertex3f(-cubeSide, by - bandWidth / 2, -cubeSide - bandDepth);
	glVertex3f(-cubeSide - bandDepth, by - bandWidth / 2, -cubeSide - bandDepth);
	glEnd();
}

void finishWrapping(char side) {
	//calculate cbx, cby, cbz and make the last wrap to the limit
	//based also on elasticityCoef and extraSize
	switch (side) {
	//side can be front(f), right(r), back(b) or left(l)
	//for testing it will always end in front
	case 'f':
		//if (copyBandLength < cbx + cubeSide && copyBandLength + (bandLength + bandLength*elasticityCoef - (cubeSide - bx + bandDepth) - 
			//(2 * cubeSide + bandDepth) * (nrOfWraps - 1)) < cbx + cubeSide) cbx = (bandLength + bandLength*elasticityCoef - (cubeSide - bx + bandDepth) -
				//(2 * cubeSide + bandDepth) * (nrOfWraps - 1)) - cubeSide;//not good, rethink this!!!!
		bandSideFront(true, false, 0.0, 0.5, 0.0);
		break;
	case 'r':
		bandSideRight(true, true, 0.0, 0.5, 0.0);
		bandSideBack(true, true, 0.0, 0.5, 0.0);
		bandSideLeft(true, true, 0.0, 0.5, 0.0);
		bandSideFront(true, false, 0.0, 0.5, 0.0);
		break;
	case 'b':
		bandSideBack(true, true, 0.0, 0.5, 0.0);
		bandSideLeft(true, true, 0.0, 0.5, 0.0);
		bandSideFront(true, false, 0.0, 0.5, 0.0);
		break;
	case 'l':
		bandSideLeft(true, true, 0.0, 0.5, 0.0);
		bandSideFront(true, false, 0.0, 0.5, 0.0);
		break;
	default:
		break;
	}
}

void wrapBand() {
	int wrapCount = 0;
	//yellow is the start
	//green is the end of wrap
	bandSideFront(false, true, 1, 1, 0.1);
	copyBandLength -= (cubeSide - bx + bandDepth);
	wrapCount++;
	while (copyBandLength > 0) {
		if (copyBandLength - 2 * cubeSide - bandDepth <= 0) {
			nrOfWraps = wrapCount;//how many wraps i did so far
			finishWrapping('r');
			break;
		}
		bandSideRight(); copyBandLength -= (2 * cubeSide + bandDepth);
		wrapCount++;
		if (copyBandLength - 2 * cubeSide - bandDepth <= 0) {
			nrOfWraps = wrapCount;
			finishWrapping('b');
			break;
		}
		bandSideBack(); copyBandLength -= (2 * cubeSide + bandDepth);
		wrapCount++;
		if (copyBandLength - 2 * cubeSide - bandDepth <= 0) {
			nrOfWraps = wrapCount;
			finishWrapping('l');
			break;
		}
		bandSideLeft(); copyBandLength -= (2 * cubeSide + bandDepth);
		wrapCount++;
		if (copyBandLength - 2 * cubeSide - bandDepth <= 0) {
			nrOfWraps = wrapCount;
			finishWrapping('f');
			break;
		}
		//bandSideFront(); 
		copyBandLength -= (2 * cubeSide + bandDepth);
		wrapCount++;
	}
	printf("Number of wraps: %d\n", wrapCount);
	copyBandLength = bandLength;
}

void display() {

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Other Transformations
	// glTranslatef( 0.1, 0.0, 0.0 );      // Not included
	// glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	// Other Transformations
	// glScalef( 2.0, 2.0, 0.0 );          // Not included

	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);     glVertex3f(cubeSide, -cubeSide, -cubeSide);      // P1 is red
	glColor3f(0.0, 1.0, 0.0);     glVertex3f(cubeSide, cubeSide, -cubeSide);      // P2 is green
	glColor3f(0.0, 0.0, 1.0);     glVertex3f(-cubeSide, cubeSide, -cubeSide);      // P3 is blue
	glColor3f(1.0, 0.0, 1.0);     glVertex3f(-cubeSide, -cubeSide, -cubeSide);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(cubeSide, -cubeSide, cubeSide);
	glVertex3f(cubeSide, cubeSide, cubeSide);
	glVertex3f(-cubeSide, cubeSide, cubeSide);
	glVertex3f(-cubeSide, -cubeSide, cubeSide);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(cubeSide, -cubeSide, -cubeSide);
	glVertex3f(cubeSide, cubeSide, -cubeSide);
	glVertex3f(cubeSide, cubeSide, cubeSide);
	glVertex3f(cubeSide, -cubeSide, cubeSide);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-cubeSide, -cubeSide, cubeSide);
	glVertex3f(-cubeSide, cubeSide, cubeSide);
	glVertex3f(-cubeSide, cubeSide, -cubeSide);
	glVertex3f(-cubeSide, -cubeSide, -cubeSide);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(cubeSide, cubeSide, cubeSide);
	glVertex3f(cubeSide, cubeSide, -cubeSide);
	glVertex3f(-cubeSide, cubeSide, -cubeSide);
	glVertex3f(-cubeSide, cubeSide, cubeSide);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(cubeSide, -cubeSide, -cubeSide);
	glVertex3f(cubeSide, -cubeSide, cubeSide);
	glVertex3f(-cubeSide, -cubeSide, cubeSide);
	glVertex3f(-cubeSide, -cubeSide, -cubeSide);
	glEnd();

	wrapBand();

	glFlush();
	glutSwapBuffers();

}

void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

bool checkInput() {
	printf("cubeSide: %lf\nbandLength: %lf\nbandWidth: %lf\nbandDepth: %lf\nbx: %lf\nby: %lf\nbz: %lf\nelasticityCoef: %lf\nextraSpace: %lf\n", cubeSide,
		bandLength, bandWidth, bandDepth, bx, by, bz, elasticityCoef, extraSpace);
	if (cubeSide > 1 || cubeSide < 0 ||
		bandDepth > 1 || bandDepth < 0 ||
		bandWidth > 1 || bandWidth < 0 ||
		bandLength < 0) {
		printf("cubeSide, bandinfo bigger than 1 or lower than 0. Error!\n");
		return false;
	}
	if (bandDepth >= cubeSide || bandWidth >= cubeSide) return false;//if is too thick
	if (by > cubeSide || bx > cubeSide ||
		by < -cubeSide ||bx < -cubeSide) return false; //if is outside of the cube
	if (by + bandWidth / 2 > cubeSide || by - bandWidth / 2 < -cubeSide) return false; //if the band is going a bit out of the cube with the width
	if (bandLength < cubeSide * 8 + bandDepth * 4) return false; //cannot wrap not at least one time
	{
		//check if it can be wrapped with elasticityCoef and extraSize
		double tempCubeLength = cubeSide * 8 + bandDepth * 4, tempLength = bandLength, counter = 0;
		while (tempLength >= tempCubeLength) {
			tempLength -= tempCubeLength;
			counter++;
		}
		double distToOrigin = bx + cubeSide;
		if ((bandLength + bandLength*elasticityCoef - counter*tempCubeLength) >= distToOrigin && distToOrigin >= tempLength ||
			(bandLength + bandLength*elasticityCoef - counter*tempCubeLength + extraSpace) >= distToOrigin && distToOrigin >= tempLength) {
			straightToOrigin = true;
		}
		else {
			printf("\n>>Counter is %lf, while tempLength is %lf\n", counter, tempLength);
			printf(">>Cannot wrap the band so that it is close to the starting point of wrapping!\n");
			return false;
		}
	}

	return true;
}

void getInput(bool file=true) {
	if (!file) {
		printf("The following data must be real numbers between 0 and 1\n");
		printf("Insert the length of the side of the cube here: ");
		scanf("%lf", &cubeSide);
		printf("Insert here the length, width and depth of the band: ");
		scanf("%lf %lf %lf", &bandLength, &bandWidth, &bandDepth);
		printf("Choose coordinates from where the band wrapping should start(x,y,z): ");
		scanf("%lf %lf %lf", &bx, &by, &bz);
		printf("Write the elasticity coeficient(x%) for the band and the extra \"error\" space needed for wrapping:");
		scanf("%lf %lf", &elasticityCoef, &extraSpace);
	}
	else {
		FILE* f;
		f = fopen("Input.txt", "r+");
		fscanf(f,"cubeSide: %lf\nbandLength: %lf\nbandWidth: %lf\nbandDepth: %lf\nbx: %lf\nby: %lf\nbz: %lf\nelasticityCoef: %lf\nextraSpace: %lf\n", &cubeSide, 
			&bandLength, &bandWidth, &bandDepth, &bx, &by, &bz, &elasticityCoef, &extraSpace);
		fclose(f);
	}
	//edit input
	//#1# find the point on the front side that match the coordinates
	bz = -cubeSide;

	cbx = bx; cby = by; cbz = bz;//coordinates to edit the end
	elasticityCoef /= 100;
	maxBandLength = bandLength + bandLength*elasticityCoef;
	copyBandLength = bandLength;
}

int main(int argc, char* argv[]) {

	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	getInput();
	if (!checkInput()) {
		printf("\n\t\t\t\t***Bad input***!\n\n");
		system("pause");
		return 0;
	}

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutCreateWindow("Awesome Cube Wrapping");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;
}