#include "Mass.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

static float rt = 0.0f;

Mass::Mass()
: Entity()
, r(0.0f)
, color(1.0f, 1.0f, 1.0f, 1.0f)
{}


Mass::Mass(float m_, float r_, Vector3 pos_, Vector3 vel_)
: Entity(m_, pos_, vel_, Color4f(0.0f, 0.0f, 0.0f, 0.0f))
, r(r_)
{
}

void Mass::Set(float m, float r, Vector3 p, Vector3 v, Color4f color)
{
	this->m = m;
	this->r = r;
	this->pos = p;
	this->vel = v;	
	this->color = color;
	//this->isLight = isLight;
}

void Mass::update(float dt)
{
	this->pos += this->vel * dt;
}

void Mass::Draw()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	gluQuadricTexture(quadratic, GL_FALSE);

	glPushMatrix();
	
	glTranslatef(GetPos().x, GetPos().y, GetPos().z);
	//glRotatef(-90.0f, 1, 0, 0);
	//glRotatef(rt, 0, 0, 1);
	//rt += 0.1f;
	
	//r += 0.001f;

	glColor3f(GetColor().r, GetColor().g, GetColor().b);


	//glBindTexture(GL_TEXTURE_2D, GLuint(4));			// Select Texture 2 (1)
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	//glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping	
	
	gluSphere(quadratic, GetR(), 32, 16); 
	//   		if (mGame.Entities[i].isLight)
	//   			glEnable(GL_LIGHTING);

	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	//glBindTexture(GL_TEXTURE_2D, GLuint(0));

	glPopMatrix();
	
	gluDeleteQuadric(quadratic);
}