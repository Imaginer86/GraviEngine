#include "Line.h"

#include "..\gl\glaux.h"

#include "..\Math\Math.h"

void Line::Draw()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	//gluQuadricDrawStyle(quadratic, GLU_LINE);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)

	glPushMatrix();
	Vector3 h = (pos + pos2) - (pos = pos2);
	Vector3 h_u = h.unit();
	//glTranslatef(mGame.lines[i].pos1.x, mGame.lines[i].pos1.y, mGame.lines[i].pos1.z);

	float angle_x = atan2(h.y, h.z);
	angle_x = Math::ToDegree(angle_x);

	float angle_y = atan2(h.x, h.z);
	angle_y = Math::ToDegree(angle_y);

	float angle_z = atan2(h.x, h.y);
	angle_z = Math::ToDegree(angle_z);

	//glRotatef(-45, 1, 0, 0);
	//glRotatef(45, 0, 1, 0);		
	//glRotatef(45, 0, 0, 1);

	//glRotatef(temp_angle, 1, 1, 0);
	//glTranslatef(10, 0, 0);
	//glRotatef(temp_angle, 1, 1, 0);

	//glRotatef(90, 0, 1, 0);
	//temp_angle += 0.5;

	glColor3f(color.r, color.g, color.b );
	gluCylinder(quadratic, r, r, h.length(), 32, 32);
	// 		//gluDisk(quadratic, 0, mGame.lines[i].r, 32, 32);

// 	glBegin(GL_LINES);
// 		glColor3f(1, 0, 0);
// 		glVertex3f(0, 0, 0);
// 		glVertex3f(0, 0, h.length());
// 	glEnd();	 

	glTranslatef(0, 0, h.length());
 	gluSphere(quadratic, r , 32, 32);

	glTranslatef(0, 0, -h.length());
	gluSphere(quadratic, r , 32, 32);


	glPopMatrix();		

	gluDeleteQuadric(quadratic);
}
