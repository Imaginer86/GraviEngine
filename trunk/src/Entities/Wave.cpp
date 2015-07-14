﻿#include "Wave.h"

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

	float hangle = 360.0f/float(numRo);

	glTranslatef(0.0f, 4.0f, 0.0f);

	glBegin(GL_QUADS);       // Начало рисования четырехугольников


	glColor3f(color.r+0.4f, color.g, color.b);

	Vector3 pos0, pos1, pos2, pos3;
	Vector3 normal;

	//pos0 = pos;
	//pos1 = pos0 + Vector3(0.0f, 0.0f, w);

	for (unsigned r = 0; r < numR; r++)
	{
		for (unsigned ro = 0; ro < numRo; ro++)
		{
			float angle0 = Math::degreesToRadians(hangle*ro);
			float angle1 = Math::degreesToRadians(hangle*(ro + 1));
			float dist0 = r*w;
			float dist1 = (r + 1)*w;

			pos0 = Vector3(dist0*cosf(angle0), 3 * sqrtf(tGame) * sinf(2 * (dist0 - tGame)) / (dist0 + tGame), dist0*sinf(angle0));
			pos1 = Vector3(dist1*cosf(angle0), 3 * sqrtf(tGame) * sinf(2 * (dist1 - tGame)) / (dist1 + tGame), dist1*sinf(angle0));
			pos2 = Vector3(dist1*cosf(angle1), 3 * sqrtf(tGame) * sinf(2 * (dist1 - tGame)) / (dist1 + tGame), dist1*sinf(angle1));
			pos3 = Vector3(dist0*cosf(angle1), 3 * sqrtf(tGame) * sinf(2 * (dist0 - tGame)) / (dist0 + tGame), dist0*sinf(angle1));

			
			//Vector3 pos2d = Vector3(dist*cosf(Math::degreesToRadians(angle)), 10 * sqrtf(tGame)*sinf(dist - tGame) / (dist + tGame), dist*sinf(Math::degreesToRadians(angle)));
			//Vector3 pos3d = Vector3(dist0*cosf(Math::degreesToRadians(angle)), 10 * sqrtf(tGame)*sinf(dist0 - tGame) / (dist0 + tGame), dist0*sinf(Math::degreesToRadians(angle)));

			//Vector3 pos2d = Vector3(dist*cosf(Math::degreesToRadians(angle)), 3 * sqrtf(tGame)*sinf(dist - tGame) , dist*sinf(Math::degreesToRadians(angle)));
			//Vector3 pos3d = Vector3(dist0*cosf(Math::degreesToRadians(angle)), 3 * sqrtf(tGame)*sinf(dist0 - tGame)  , dist0*sinf(Math::degreesToRadians(angle)));

			//pos2 = pos + pos2d;
			//pos3 = pos + pos3d;
			normal = (pos1 - pos0)*(pos3 - pos0);

			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(pos0.x, pos0.y, pos0.z);
			glVertex3f(pos1.x, pos1.y, pos1.z);
			glVertex3f(pos2.x, pos2.y, pos2.z);			
			glVertex3f(pos3.x, pos3.y, pos3.z);
			pos0 = pos3;
			pos1 = pos2;
		}		 
		//pos0 = pos1;
		//pos1 = pos0 + Vector3(0.0f, 0.0f, w);
	}
	glEnd();

	glPopMatrix();
}