/*
//#include "..\gl\glaux.h"
#include "Line.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

Line::Line()
: Entity()
, r(1.0f)
, h(1.0f)
, q(0.0f, 0.0f, 0.0f, 0.0f)
, force(0.0f, 0.0f, 0.0f)
{
	this->color.r = 1.0f;
	this->color.g = 1.0f;
	this->color.b = 1.0f;
	this->color.a = 1.0f;
}

void Line::Draw()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	//gluQuadricDrawStyle(quadratic, GLU_LINE);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)

	glPushMatrix();
	//Vector3 h_u = h.unit();
	//glTranslatef(mGame.lines[i].pos1.x, mGame.lines[i].pos1.y, mGame.lines[i].pos1.z);

// 	float angle_x = atan2(h.y, h.z);
// 	angle_x = Math::ToDegree(angle_x);
// 
// 	float angle_y = atan2(h.x, h.z);
// 	angle_y = Math::ToDegree(angle_y);
// 
// 	float angle_z = atan2(h.x, h.y);
// 	angle_z = Math::ToDegree(angle_z);

	//glRotatef(-45, 1, 0, 0);
	//glRotatef(45, 0, 1, 0);		
	//glRotatef(45, 0, 0, 1);

	//glRotatef(temp_angle, 1, 1, 0);
	//glTranslatef(10, 0, 0);
	//glRotatef(temp_angle, 1, 1, 0);

	//glRotatef(90, 0, 1, 0);
	//temp_angle += 0.5;

	glTranslatef(pos.x, pos.y, pos.z - h/2.0);
	float headDegrees = 0.0, pitchDegrees = 0.0, rollDegrees = 0.0;
//	q.toHeadPitchRoll( headDegrees, pitchDegrees, rollDegrees);
	glRotatef(headDegrees, 1, 0, 0);
	glRotatef(pitchDegrees, 0, 1, 0);
	glRotatef(rollDegrees, 0, 0, 1);
	//q.y += 1;				  
	glColor4f(color.r, color.g, color.b );
	gluCylinder(quadratic, r, r, h, 32, 32);
	// 		//gluDisk(quadratic, 0, mGame.lines[i].r, 32, 32);

// 	glBegin(GL_LINES);
// 		glColor4f(1, 0, 0);
// 		glVertex3f(0, 0, 0);
// 		glVertex3f(0, 0, h.length());
// 	glEnd();

	glPushMatrix();
	glTranslatef(0, 0, h);
	gluSphere(quadratic, r , 32, 32);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(0, 0, h/2.0f);	
	gluSphere(quadratic, r , 32, 32);
	glPopMatrix();

	glPopMatrix();		

	gluDeleteQuadric(quadratic);
}
*/