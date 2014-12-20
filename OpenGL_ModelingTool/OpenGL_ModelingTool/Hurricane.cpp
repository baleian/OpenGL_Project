#include "Hurricane.h"
#include "common.h"


Hurricane::Hurricane()
{
	rotCase = 0, rotPivot = 0;
}


Hurricane::~Hurricane()
{
}


static void DrawHurricaneCase(void)
{
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

	Vector3D p, p2;

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, Texture::getInstance()->texSteel1);
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

	glBindTexture(GL_TEXTURE_2D, Texture::getInstance()->texCaptainShield);
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

	glBindTexture(GL_TEXTURE_2D, Texture::getInstance()->texSteel1);
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

static void DrawHurricanePivot(void)
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
	glBindTexture(GL_TEXTURE_2D, Texture::getInstance()->texSteel2);
	glPushMatrix();
	glTranslated(0, 1.05, 0);
	glBegin(GL_QUAD_STRIP);
	{
		glTexCoord2f(0, 0);
		glVertex3f(1, -0.35, -0.35);
		glTexCoord2f(0, 0);
		glVertex3f(-1, -0.35, -0.35);
		glTexCoord2f(0, 0);
		glVertex3f(1, 0.35, -0.35);
		glTexCoord2f(0, 0);
		glVertex3f(-1, 0.35, -0.35);
		glTexCoord2f(0, 0);
		glVertex3f(1, 0.35, 0.35);
		glTexCoord2f(0, 0);
		glVertex3f(-1, 0.35, 0.35);
		glTexCoord2f(0, 0);
		glVertex3f(1, -0.35, 0.35);
		glTexCoord2f(0, 0);
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

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 10, 0);
	DrawCylinder(0.5, 0.5, 3);
	glPopMatrix();

	glPopAttrib();
}

static void DrawHurricaneBody(void)
{
	glPushAttrib(GL_CURRENT_BIT);

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslated(0, 0, -3.5);
	glRotated(20, 1, 0, 0);
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(20, 0, 1, 0);
	glTranslatef(-3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();

	glColor3f(1, 1, 1);
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

	glColor3f(1, 0, 0);
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
	glTranslatef(3, 0, 0);
	DrawCylinder(0.5, 0.1, 14);
	glPopMatrix();
	glPopMatrix();

	glPopAttrib();
}


GLfloat Hurricane::getRotateCase(void)
{
	return this->rotCase;
}

void Hurricane::setRotateCase(GLfloat rotCase)
{
	this->rotCase = rotCase;
}

GLfloat Hurricane::getRotatePivot(void)
{
	return this->rotPivot;
}

void Hurricane::setRotatePivot(GLfloat rotPivot)
{
	this->rotPivot = rotPivot;
}

void Hurricane::Draw(void)
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);

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

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 10.3, 1.5);
	DrawCaptainShield();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glTranslatef(0, 10.3, 1.5);
	DrawCaptainShield();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 3, 0);
	DrawHurricaneBody();
	glPopMatrix();

	glPopAttrib();
}



