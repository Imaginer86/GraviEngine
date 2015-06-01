#include "Wave.h"
#include "..\Math\Vector3.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

void Wave::Update(float dt_)
{
	this->tGame += 5*dt_;
}

void Wave::Draw()
{
	glPushMatrix();

	float w = 0.2f;
	float hangle= 10.0f;
	float t = 1;

	glBegin(GL_QUADS);       // Начало рисования четырехугольников

	glColor3f(0, 0, 0.5f);

	Vector3 pos0, pos1, pos2, pos3;
	pos1 = pos0 + Vector3(0.0f, 0.0f, w);

	for (unsigned r = 1; r < 128; r++)
	{
		for (unsigned ro = 1; ro <= 36; ro++)
		{
			float angle = hangle*ro;
			float dist = r*w;
			float dist0 = (r - 1)*w;
			//if (tGame > 1.0f)
			//{
			pos2 = Vector3(dist*sinf(Math::degreesToRadians(angle)), 3 * sqrtf(tGame)*sinf(dist - tGame) / (dist + tGame), dist*cosf(Math::degreesToRadians(angle)));
			pos3 = Vector3(dist0*sinf(Math::degreesToRadians(angle)), 3 * sqrtf(tGame)*sinf(dist0 - tGame) / (dist0 + tGame), dist0*cosf(Math::degreesToRadians(angle)));
			//}
			//else
			//{
				//pos2 = Vector3(dist*sinf(Math::degreesToRadians(angle)), sqrtf(dist)*sinf(dist - tGame) / (dist), dist*cosf(Math::degreesToRadians(angle)));
				//pos3 = Vector3(dist0*sinf(Math::degreesToRadians(angle)), sqrtf(dist0)*sinf(dist0 - tGame) / (dist0), dist0*cosf(Math::degreesToRadians(angle)));
			//}
			glVertex3f(pos0.x, pos0.y, pos0.z);
			glVertex3f(pos1.x, pos1.y, pos1.z);
			glVertex3f(pos2.x, pos2.y, pos2.z);
			glVertex3f(pos3.x, pos3.y, pos3.z);
			pos0 = pos3;
			pos1 = pos2;
		}		
	}
	glEnd();

	glPopMatrix();
}