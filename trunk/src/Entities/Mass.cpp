#include "Mass.h"

//#include <gl\GL.h>
//#include <gl\GLU.h>
#include "..\gl\glaux.h"

static float rt = 0.0f;

void Mass::Draw()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	//gluQuadricDrawStyle(quadratic, GLU_LINE);
	//gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	gluQuadricTexture(quadratic, GL_TRUE);

	glPushMatrix();
	
	glTranslatef(GetPos().x, GetPos().y, GetPos().z);
	glRotatef(rt, 0, 1, 0);
	//rt += 0.1f;
	
	//r += 0.001f;

	glColor3f(GetColor().r, GetColor().g, GetColor().b);


	glBindTexture(GL_TEXTURE_2D, GLuint(4));			// Select Texture 2 (1)
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping


	
	gluSphere(quadratic, GetR(), 32, 16); 
	//   		if (mGame.Entities[i].isLight)
	//   			glEnable(GL_LIGHTING);

	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	glBindTexture(GL_TEXTURE_2D, GLuint(0));
	glPopMatrix();				
	gluDeleteQuadric(quadratic);
}