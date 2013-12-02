#include "Mass.h"

//#include <gl\GL.h>
//#include <gl\GLU.h>
#include "..\gl\glaux.h"

void Mass::Draw()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	//gluQuadricDrawStyle(quadratic, GLU_LINE);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	glPushMatrix();
	glTranslatef(GetPos().x, GetPos().y, GetPos().z);
	glColor3f(GetColor().r, GetColor().g, GetColor().b);
	gluSphere(quadratic, GetR(), 32, 32); 
	//   		if (mGame.Entities[i].isLight)
	//   			glEnable(GL_LIGHTING);
	glPopMatrix();				
	gluDeleteQuadric(quadratic);
}