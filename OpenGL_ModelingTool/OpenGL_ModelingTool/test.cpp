#include <Windows.h>
#include "common.h"
#include <stdio.h>


#define INIT_HARF_WIDTH	5


GLfloat halfwidth = INIT_HARF_WIDTH;
GLfloat x_t = 0;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

GLenum PolygonMode = GL_LINE;
bool axisMode = true;
bool aniMode = false;
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
		glDisable(GL_CULL_FACE);
		PolygonMode = GL_POINT;
		break;
	case 2:
		glDisable(GL_CULL_FACE);
		PolygonMode = GL_LINE;
		break;
	case 3:
		glEnable(GL_CULL_FACE);
		PolygonMode = GL_FILL;
		break;
	case 4:
		axisMode = !axisMode;
		break;
	case 5:
		aniMode = !aniMode;
		CaptainAmericaWorld::getInstance()->Animation(aniMode);
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
		for (int i = 0; i < 999; i += 1) {
			glVertex3d(i, 0, 999);
			glVertex3d(-i, 0, 999);
			glVertex3d(0, i, 999);
			glVertex3d(0, -i, 999);
		}
	}
	glEnd();


	glPointSize(2);
	glBegin(GL_POINTS);
	{
		for (float i = 0; i < 999; i += 0.1) {
			glColor3f(1, 0, 0);
			glVertex3d(i, 0, 999);
			glVertex3d(-i, 0, 999);

			glColor3f(0, 1, 0);
			glVertex3d(0, i, 999);
			glVertex3d(0, -i, 999);
		}
	}
	glEnd();

	glPopAttrib();
}


void DoDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CCW);
		

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfwidth + x_t, halfwidth + x_t, -halfwidth, halfwidth, -1000, 1000);
	/*
	gluPerspective(45.0f, 1.0f, 0.001f, 1000);
	gluLookAt(
		0, 0, -30,
		0, 0, 1,
		0, 1, 0
		);

	*/
	if (axisMode) {
		DrawAxis();
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glRotatef(xRot, 0, 1, 0);
	glRotatef(yRot, 1, 0, 0);

	glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);
	glColor3f(1, 1, 1);	// Default polygon color.

	glPushMatrix();
	{
		CaptainAmericaWorld::getInstance()->Draw();
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
	glutAddMenuEntry("Animation ON/OFF", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}


/***********************************
* 그리기 테스트 정의 부분.
***********************************/


/*





void DrawCaptianShield(void)
{
	
}



void DrawHurricane(GLfloat rotCase, GLfloat rotPivot)
{
	
}


*/