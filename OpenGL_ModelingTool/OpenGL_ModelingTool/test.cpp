#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include "Vector3D.h"

#define PI	3.14159265358979323846f

#define INIT_HARF_WIDTH	3

GLfloat halfwidth = INIT_HARF_WIDTH;
GLfloat x_t = 0;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

GLenum PolygonMode = GL_LINE;
bool axisMode = true;

int x_prev, y_prev;

void DrawTest(void);

void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': halfwidth -= 0.5; break;
	case 's': halfwidth += 0.5; break;
	case 'a': x_t -= 0.5; break;
	case 'd': x_t += 0.5; break;

	case 'z':
		halfwidth = INIT_HARF_WIDTH;
		xRot = 0.0f;
		yRot = 0.0f;
		break;
	default:
		return;
	}

	if (halfwidth < 0.5) {
		halfwidth = 0.5;
	}

	glutPostRedisplay();
}

void DoMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		x_prev = x;
		y_prev = y;
	}
}

void DoMouseDrag(int x, int y)
{
	if (x_prev < x) {
		xRot += 1.0f;
		x_prev = x;

	}
	else if (x_prev > x) {
		xRot -= 1.0f;
		x_prev = x;
	}

	else if (y_prev > y) {
		yRot -= 1.0f;
		y_prev = y;
	}
	else if (y_prev < y) {
		yRot += 1.0f;
		y_prev = y;
	}
	else {
		return;
	}

	glutPostRedisplay();
}

void DoMenu(int value)
{
	switch (value) {
	case 1:
		PolygonMode = GL_POINT;
		break;
	case 2:
		PolygonMode = GL_LINE;
		break;
	case 3:
		PolygonMode = GL_FILL;
		break;
	case 4:
		axisMode = !axisMode;
		break;
	}

	glutPostRedisplay();
}

void DrawAxis(void)
{
	glPushAttrib(GL_POINT_SIZE);

	glColor3f(1, 1, 1);

	glPointSize(4);
	glBegin(GL_POINTS);
	{
		glColor3f(1, 1, 1);
		for (int i = 0; i < 1000; i += 1) {
			glVertex3d(i, 0, 1000);
			glVertex3d(-i, 0, 1000);
			glVertex3d(0, i, 1000);
			glVertex3d(0, -i, 1000);
		}
	}
	glEnd();


	glPointSize(2);
	glBegin(GL_POINTS);
	{
		for (float i = 0; i < 1000; i += 0.1) {
			glColor3f(1, 0, 0);
			glVertex3d(i, 0, 1000);
			glVertex3d(-i, 0, 1000);

			glColor3f(0, 1, 0);
			glVertex3d(0, i, 1000);
			glVertex3d(0, -i, 1000);
		}
	}
	glEnd();

	glPopAttrib();
}

void DoDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfwidth + x_t, halfwidth + x_t, -halfwidth, halfwidth, -1000, 1000);

	if (axisMode) {
		DrawAxis();
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glRotatef(xRot, 0, 1, 0);
	glRotatef(yRot, 1, 0, 0);


	glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);
	glPushMatrix();
	{
		glColor3f(1, 1, 1);	// Default polygon color.
		DrawTest();
	}
	glPopMatrix();


	glPopMatrix();
	glutSwapBuffers();
}


void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}


void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 1200);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("12091602_이범준");
	glutMouseFunc(DoMouseClick);
	glutMotionFunc(DoMouseDrag);
	glutKeyboardFunc(DoKeyboard);

	glutCreateMenu(DoMenu);
	glutAddMenuEntry("Polygon POINT", 1);
	glutAddMenuEntry("Polygon LINE", 2);
	glutAddMenuEntry("Polygon FILL", 3);
	glutAddMenuEntry("Axis ON/OFF", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}



/***********************************
* 그리기 테스트 정의 부분.
***********************************/
void DrawTest(void)
{
	Vector3D v1(0.2, 0, -0.04);
	Vector3D v2(0.5, 0, -0.04);

	Vector3D v3(0.2, 0, 0.04);
	Vector3D v4(0.5, 0, 0.04);

	Vector3D v5(0.2, 0, 0.04);
	Vector3D v6(0.2, 0, -0.04);

	Vector3D v7(0.5, 0, 0.04);
	Vector3D v8(0.5, 0, -0.04);


	glBegin(GL_QUAD_STRIP);
	for (GLfloat a = 0.0f; a < 2 * PI; a += PI / 16) {
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		v1.RotateAboutZ(PI / 16);
		v2.RotateAboutZ(PI / 16);
	}
	glVertex3f(0.2, 0, -0.04);
	glVertex3f(0.5, 0, -0.04);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (GLfloat a = 0.0f; a < 2 * PI; a += PI / 16) {
		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v4.x, v4.y, v4.z);
		v3.RotateAboutZ(PI / 16);
		v4.RotateAboutZ(PI / 16);
	}
	glVertex3f(0.2, 0, 0.04);
	glVertex3f(0.5, 0, 0.04);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (GLfloat a = 0.0f; a < 2 * PI; a += PI / 16) {
		glVertex3f(v5.x, v5.y, v5.z);
		glVertex3f(v6.x, v6.y, v6.z);
		v5.RotateAboutZ(PI / 16);
		v6.RotateAboutZ(PI / 16);
	}
	glVertex3f(0.2, 0, 0.04);
	glVertex3f(0.2, 0, -0.04);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (GLfloat a = 0.0f; a < 2 * PI; a += PI / 16) {
		glVertex3f(v7.x, v7.y, v7.z);
		glVertex3f(v8.x, v8.y, v8.z);
		v7.RotateAboutZ(PI / 16);
		v8.RotateAboutZ(PI / 16);
	}
	glVertex3f(0.5, 0, 0.04);
	glVertex3f(0.5, 0, -0.04);
	glEnd();
}