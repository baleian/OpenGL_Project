#include <Windows.h>
#include "common.h"
#include <stdio.h>


enum MODE { WORLD, MODELING } mode;


GLenum PolygonMode = GL_FILL;
bool axisMode = true;
bool aniMode = true;
int x_prev, y_prev;

void DrawTest(void);

void SetupRC(void)
{
	halfwidth = INIT_HARF_WIDTH;
	xRot = 0.0f;
	yRot = 0.0f;

	CaptainAmericaWorld::getInstance()->Animation(aniMode);
}

void DoKeyboard(unsigned char key, int x, int y)
{
	if (mode == WORLD) {
		WorldDoKeyboard(key, x, y);
	}
	else {
		switch (key) {
		case 'w': case 'W': halfwidth -= 0.5; break;
		case 's': case 'S': halfwidth += 0.5; break;
		case 'a': case 'A': x_t -= 0.5; break;
		case 'd': case 'D': x_t += 0.5; break;
		case 'z': case 'Z':
			SetupRC();
			break;
		default:
			return;
		}
	

		if (halfwidth < 0.5) {
			halfwidth = 0.5;
		}

		glutPostRedisplay();
	}
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
	if (mode == WORLD) {
		WorldDoMouseDrag(x_prev, y_prev, x, y);
	}
	else {
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
		aniMode = !aniMode;
		CaptainAmericaWorld::getInstance()->Animation(aniMode);
		break;
	case 5:
		if (mode == WORLD) {
			mode = MODELING;
		}
		else {
			mode = WORLD;
		}
		SetupRC();
		break;
	case 6:
		axisMode = !axisMode;
		break;
	case 7:
		CaptainAmericaWorld::getInstance()->SetViewingCam(0);
		break;
	case 8:
		CaptainAmericaWorld::getInstance()->SetViewingCam(1);
		break;
	case 9:
		CaptainAmericaWorld::getInstance()->SetViewingCam(2);
		break;
	case 10:
		CaptainAmericaWorld::getInstance()->SetViewingCam(3);
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
	
	if (PolygonMode == GL_FILL) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);
	glColor3f(1, 1, 1);	// Default polygon color.

	glPushMatrix();
	{
		if (mode == WORLD) {
			CaptainAmericaWorld::getInstance()->Draw();
		}
		else {
			glOrtho(-halfwidth + x_t, halfwidth + x_t, -halfwidth, halfwidth, -1000, 1000);

			if (axisMode) {
				DrawAxis();
			}

			glRotatef(xRot, 0, 1, 0);
			glRotatef(yRot, 1, 0, 0);
			DrawTest();
		}
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
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("12091602_이범준 - Captain America World");
	glutMouseFunc(DoMouseClick);
	glutMotionFunc(DoMouseDrag);
	glutKeyboardFunc(DoKeyboard);

	glutCreateMenu(DoMenu);
	glutAddMenuEntry("Polygon POINT", 1);
	glutAddMenuEntry("Polygon LINE", 2);
	glutAddMenuEntry("Polygon FILL", 3);
	glutAddMenuEntry("Animation ON/OFF", 4);
	glutAddMenuEntry("World / Modeling", 5);
	glutAddMenuEntry("Axis ON/OFF", 6);
	glutAddMenuEntry("Free View", 7);
	glutAddMenuEntry("Viking View", 8);
	glutAddMenuEntry("Hurricane View", 9);
	glutAddMenuEntry("Train View", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	WorldSetupRC();
	glutMainLoop();
}


/***********************************
* 그리기 테스트 정의 부분.
***********************************/


#include "Hurricane.h"
Hurricane hurricane;
void DrawTest(void)
{
	hurricane.Draw();
}