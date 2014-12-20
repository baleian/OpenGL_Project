#include <Windows.h>
#include "common.h"
#include <stdio.h>
#include <math.h>
#include "Vector3D.h"



#define INIT_HARF_WIDTH	3



GLfloat halfwidth = INIT_HARF_WIDTH;
GLfloat x_t = 0;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

GLenum PolygonMode = GL_LINE;
bool axisMode = true;
bool aniMode = false;
int x_prev, y_prev;

void DrawTest(void);
void DoTimer(int);

void SetupRC(void)
{
	
}

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
		if (aniMode) {
			glutTimerFunc(0, DoTimer, 1);
		}
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

Vector3D getNormalVector(Vector3D a, Vector3D b, Vector3D c)
{
	return ((b - a) % (c - a)).Normalize();
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
	glutAddMenuEntry("Animation ON/OFF", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
}


/***********************************
* 그리기 테스트 정의 부분.
***********************************/
/*
void DrawHurricaneCase(void)
{
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

	Vector3D p, p2;
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textId[1]);
	p = Vector3D(3, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	{
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glTexCoord2f(p.x, p.z);
			glVertex3f(p.x, p.y, p.z);
			p.RotateAboutY(-PI / 30);
		}
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textId[0]);
	p = Vector3D(3, 0.3, 0);
	p2 = Vector3D(0.2, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	{
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0.3, 0);
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glTexCoord2f(p2.x + 0.5, p2.z + 0.5);
			glVertex3f(p.x, p.y, p.z);
			p.RotateAboutY(PI / 30);
			p2.RotateAboutY(PI / 30);
		}
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textId[1]);
	p = Vector3D(3, 0, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glTexCoord2f(p.x, p.z);
			glVertex3f(p.x, p.y, p.z);
			glTexCoord2f(p.x, p.z + 0.3);
			glVertex3f(p.x, p.y + 0.3, p.z);
			p.RotateAboutY(-PI / 30);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 0, 0);
	p = Vector3D(3, 0.3, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y + 0.7, p.z);
			p.RotateAboutY(-PI / 30);
		}
	}
	glEnd();

	p = Vector3D(2.95, 0.3, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y + 0.7, p.z);
			p.RotateAboutY(PI / 30);
		}
	}
	glEnd();

	p = Vector3D(2.95, 1, 0);
	p2 = Vector3D(3, 1, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p2.x, p2.y, p2.z);
			p.RotateAboutY(PI / 30);
			p2.RotateAboutY(PI / 30);
		}
	}
	glEnd();

	glColor3f(0, 1, 0);
	// 1미터 반지름에 높이 50센티 20센티의 두깨
	p = Vector3D(1, 0.3, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y + 0.5, p.z);
			p.RotateAboutY(-PI / 30);
		}
	}
	glEnd();

	p = Vector3D(0.8, 0.3, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y + 0.5, p.z);
			p.RotateAboutY(PI / 30);
		}
	}
	glEnd();

	p = Vector3D(0.8, 0.8, 0);
	p2 = Vector3D(1, 0.8, 0);
	glBegin(GL_QUAD_STRIP);
	{
		for (GLfloat angle = 0; angle <= 2 * PI; angle += PI / 30) {
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p2.x, p2.y, p2.z);
			p.RotateAboutY(PI / 30);
			p2.RotateAboutY(PI / 30);
		}
	}
	glEnd();

	glPopAttrib();
}

void DrawCylinder(GLfloat base_radius, GLfloat top_radius, GLfloat height)
{
	glPushMatrix();
	glTranslatef(0, 0, -height / 2);
	GLUquadric *pQuad;
	pQuad = gluNewQuadric();
	gluQuadricDrawStyle(pQuad, GLU_FILL);
	gluCylinder(pQuad, base_radius, top_radius, height, 30, 30);
	glPopMatrix();
}

void DrawHurricanePivot(void)
{
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslated(0, 5, 0);
	glScalef(0.8, 10, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textId[2]);
	glPushMatrix();
	glTranslated(0, 1.05, 0);
	glBegin(GL_QUAD_STRIP);
	{
		glTexCoord2f(0, 0);
		glVertex3f(1, -0.35, -0.35);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -0.35, -0.35);
		glTexCoord2f(1, 1);
		glVertex3f(1, 0.35, -0.35);
		glTexCoord2f(1, 0);
		glVertex3f(-1, 0.35, -0.35);
		glTexCoord2f(0, 0);
		glVertex3f(1, 0.35, 0.35);
		glTexCoord2f(0, 1);
		glVertex3f(-1, 0.35, 0.35);
		glTexCoord2f(1, 1);
		glVertex3f(1, -0.35, 0.35);
		glTexCoord2f(1, 0);
		glVertex3f(-1, -0.35, 0.35);
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(-1, -0.35, 0.35);
		glTexCoord2f(0, 1);
		glVertex3f(-1, 0.35, 0.35);
		glTexCoord2f(1, 1);
		glVertex3f(-1, 0.35, -0.35);
		glTexCoord2f(1, 0);
		glVertex3f(-1, -0.35, -0.35);

		glTexCoord2f(0, 0);
		glVertex3f(1, -0.35, -0.35);
		glTexCoord2f(0, 1);
		glVertex3f(1, 0.35, -0.35);
		glTexCoord2f(1, 1);
		glVertex3f(1, 0.35, 0.35);
		glTexCoord2f(1, 0);
		glVertex3f(1, -0.35, 0.35);
	}
	glEnd();
	// glScalef(2.0, 0.7, 0.7);
	// glutSolidCube(1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 10, 0);
	DrawCylinder(0.5, 0.5, 3);
	glPopMatrix();

	glPopAttrib();
}

void DrawCaptianShield(void)
{
	
}

void DrawHurricaneBody(void)
{
	glPushMatrix();
	glTranslated(0, 0, -3.5);
	glRotated(20, 1, 0, 0);
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(20, 0, 1, 0);
	glTranslatef(-3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
	glTranslatef(3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 3.5);
	glRotated(-20, 1, 0, 0);
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(20, 0, 1, 0);
	glTranslatef(-3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
	glTranslatef(3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();
	glPopMatrix();
}

void DrawHurricane(GLfloat rotCase, GLfloat rotPivot)
{
	glPushMatrix();
	{
		glTranslatef(0, 10.3, 0);
		glRotated(rotPivot, 0, 0, 1);
		glTranslatef(0, -10.3, 0);

		glPushMatrix();
		glRotated(rotCase, 0, 1, 0);
		DrawHurricaneCase();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0.3, 0);
		DrawHurricanePivot();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10.3, 1.5);
	DrawCaptianShield();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glTranslatef(0, 10.3, 1.5);
	DrawCaptianShield();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	DrawHurricaneBody();
	glPopMatrix();
}



GLfloat hxr = 0, hyr = 0;
GLfloat hv = 3.5;
int hvec = 1, hvvec = -1;

void DrawTest(void)
{
	DrawHurricane(hxr, hyr);
}

void DoTimer(int value)
{
	if (!aniMode) {
		return;
	}
	hxr += 2;
	hyr += hv * hvec;
	hv += 0.1 * hvvec;

	if (hv <= 0) {
		hv = 0;
		hvec = -hvec;
		hvvec = -hvvec;
	}

	if (hv >= 3.5) {
		hv = 3.5;
		hvvec = -hvvec;
	}

	glutPostRedisplay();
	glutTimerFunc(20, DoTimer, 1);
}
*/

void DrawTest(void)
{

}