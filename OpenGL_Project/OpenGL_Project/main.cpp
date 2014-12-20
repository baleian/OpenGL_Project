#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include "common.h"

#define WIDTH_MIN	-100.0f
#define WIDTH_MAX	100.0f	// 100M
#define HEIGHT_MIN	-100.0f
#define HEIGHT_MAX	100.0f	// 100M
#define DEPTH_MIN	100.0f
#define DEPTH_MAX	-100.0f	// 100M
#define CAMERA_DEFAULT_HEIGHT (HEIGHT_MIN + 1.8f)

int x_prev, y_prev;
Point3D camera_pos;
Vector3D direction;
Vector3D direction_x_axis;
GLfloat max_sight;
GLfloat xAngle, yAngle;

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	camera_pos.Set(WIDTH_MIN, CAMERA_DEFAULT_HEIGHT, DEPTH_MIN);
	direction.Set(0.0f, 0.0f, -1.0f);
	direction_x_axis.Set(1.0f, 0.0f, 0.0f);
	max_sight = sqrt(pow(WIDTH_MAX - WIDTH_MIN, 2) + pow(HEIGHT_MAX - HEIGHT_MIN, 2) + pow(DEPTH_MAX - DEPTH_MIN, 2));
	xAngle = 0.0f;
	yAngle = 0.0f;
}

const GLfloat gravity = -0.0098;
GLfloat jump_a;
GLfloat jump_v;

void AnimationJump(int value)
{
	jump_v += jump_a;
	jump_a += gravity;

	char info[128];
	sprintf(info, "jump_v=%.1f, jump_a=%.1f", jump_v, jump_a);
	glutSetWindowTitle(info);

	camera_pos.y += jump_v;

	if (camera_pos.y > value) {
		glutTimerFunc(20, AnimationJump, value);
	}
	else {
		camera_pos.y = value;
	}

	glutPostRedisplay();
}

void DrawWorldTexture(void)
{
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_QUADS);
	{
		glColor3ub(0x8b, 0x8b, 0x8b);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MIN);
		glVertex3f(WIDTH_MIN, HEIGHT_MAX, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MAX, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MIN);

		glColor3ub(0xab, 0x8b, 0x8b);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MAX, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MAX, DEPTH_MAX);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MAX);

		glColor3ub(0x8b, 0x8b, 0x8b);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MAX);
		glVertex3f(WIDTH_MAX, HEIGHT_MAX, DEPTH_MAX);
		glVertex3f(WIDTH_MIN, HEIGHT_MAX, DEPTH_MAX);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MAX);

		glColor3ub(0xab, 0x8b, 0x8b);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MAX);
		glVertex3f(WIDTH_MIN, HEIGHT_MAX, DEPTH_MAX);
		glVertex3f(WIDTH_MIN, HEIGHT_MAX, DEPTH_MIN);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MIN);
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		glColor3ub(0x3b, 0x83, 0x13);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MIN);
		glVertex3f(WIDTH_MAX, HEIGHT_MIN, DEPTH_MAX);
		glVertex3f(WIDTH_MIN, HEIGHT_MIN, DEPTH_MAX);
	}
	glEnd();

	glPopAttrib();
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
	Vector3D next = camera_pos + direction;

	if (x_prev < x - 3) {
		direction.RotateAboutY(-0.01f);
		direction_x_axis.RotateAboutY(-0.01f);
		x_prev = x;
	}
	else if (x_prev > x + 3) {
		direction.RotateAboutY(0.01f);
		direction_x_axis.RotateAboutY(0.01f);
		x_prev = x;
	}
	else if (y_prev > y + 3) {
		direction.RotateAboutAxis(0.01f, direction_x_axis);
		y_prev = y;
	}
	else if (y_prev < y - 3) {
		direction.RotateAboutAxis(-0.01f, direction_x_axis);
		y_prev = y;
	}
	else {
		return;
	}

	glutPostRedisplay();
}

void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'A':
		camera_pos.x -= direction_x_axis.x;
		camera_pos.z -= direction_x_axis.z;
		break;
	case 'd':
	case 'D':
		camera_pos.x += direction_x_axis.x;
		camera_pos.z += direction_x_axis.z;
		break;
	case 'w':
	case 'W':
		camera_pos.x += direction.x;
		camera_pos.z += direction.z;
		break;
	case 's':
	case 'S':
		camera_pos.x -= direction.x;
		camera_pos.z -= direction.z;
		break;
	case 'q':
	case 'Q':
		camera_pos.y += 1.0f;
		break;
	case 'e':
	case 'E':
		camera_pos.y -= 1.0f;
		break;
	case ' ':
		jump_a = 0.16f;
		jump_v = 0.0f;
		glutTimerFunc(0, AnimationJump, camera_pos.y);
		break;
	case 'z':
	case 'Z':
		SetupRC();
		break;
	}

	if (camera_pos.x < WIDTH_MIN) {
		camera_pos.x = WIDTH_MIN;
	}

	if (camera_pos.x > WIDTH_MAX) {
		camera_pos.x = WIDTH_MAX;
	}

	if (camera_pos.y < HEIGHT_MIN) {
		camera_pos.y = HEIGHT_MIN;
	}

	if (camera_pos.y > HEIGHT_MAX) {
		camera_pos.y = HEIGHT_MAX;
	}

	if (camera_pos.z > DEPTH_MIN) {
		camera_pos.z = DEPTH_MIN;
	}

	if (camera_pos.z < DEPTH_MAX) {
		camera_pos.z = DEPTH_MAX;
	}

	glutPostRedisplay();
}

void DoDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CCW);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		Vector3D view = camera_pos + direction;
		gluLookAt(
			camera_pos.x, camera_pos.y, camera_pos.z,
			view.x, view.y, view.z,
			0, 1, 0
			);

		glPushMatrix();
		{
			// DrawWorldTexture();
		}
		glPopMatrix();


		glPushMatrix();
		{
			
			glTranslatef(0.0f, HEIGHT_MIN + 5.0f, 0.0f);
			CaptainAmericaWorld::getInstance()->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glColor3f(0.0f, 0.0f, 1.0f);
			glTranslatef(WIDTH_MIN + 5.0f, HEIGHT_MIN + 5.0f, DEPTH_MIN - 5.0f);
			glutWireSphere(5.0f, 50, 50);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.001f, max_sight);
	// glOrtho(WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX, DEPTH_MIN, DEPTH_MAX);

}


void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 1200);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("12091602_РЬЙќСи");
	glutMouseFunc(DoMouseClick);
	glutMotionFunc(DoMouseDrag);
	glutKeyboardFunc(DoKeyboard);
	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
}
