﻿#include "WaveOut.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

bool Intersect(float64 x1, float64 y1, float64 x2, float64 y2, float64 x3, float64 y3, float64 x4, float64 y4, Vector3& pos)
{
//	float64 ua = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float64 ub = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	if (ub >= 0 && ub <= 1)
	{
		pos.x = x3 + ub*(x4 - x3);
		pos.y = 0.0f;
		pos.z = y3 + ub*(y4 - y3);
		return true;
	}
	else
		return false;
}

void WaveOut::Draw()
{
	glPushMatrix();

	float64 hangle = 360.0f/float64(numRo);

	glBegin(GL_QUADS);       // Начало рисования четырехугольников

	glColor3f(color.r, color.g, color.b);

	Vector3 pos0, pos1, pos2, pos3;
	Vector3 normal;

	//pos0 = pos;
	//pos1 = pos0 + Vector3(0.0f, 0.0f, w);

	unsigned r = numR;
	{
		for (unsigned ro = 0; ro < numRo /2; ro++)
		{
			float64 angle0 = Math::degreesToRadians(hangle*float64(ro));
			float64 angle1 = Math::degreesToRadians(hangle*float64(ro + 1));
			//float64 dist0 = r*w;
			float64 dist1 = (r + 1)*w;

			//pos0 = Vector3(dist0*cosf(angle0), 0.0f, dist0*sinf(angle0));
			pos1 = Vector3(dist1*cos(angle0), 0.0f, dist1*sin(angle0));
			pos2 = Vector3(dist1*cos(angle1), 0.0f, dist1*sin(angle1));
			//pos3 = Vector3(dist0*cosf(angle1), 0.0f, dist0*sinf(angle1));

			//pos0 = Vector3(-width / 2.0f, 0.0f, -height / 2.0f);
			//pos1 = Vector3(-width / 2.0f, 0.0f, height / 2.0f);
			//pos2 = Vector3(width / 2.0f, 0.0f, height / 2.0f);
			//pos3 = Vector3(width / 2.0f, 0.0f, -height / 2.0f);


			if (Intersect(0.0f, 0.0f, pos1.x, pos1.z, -width / 2.0f, height / 2.0f, width / 2.0f, height / 2.0f, pos0) ||
				Intersect(0.0f, 0.0f, pos1.x, pos1.z, width / 2.0f, height / 2.0f, width / 2.0f, -height / 2.0f, pos0) ||
				Intersect(0.0f, 0.0f, pos1.x, pos1.z, width / 2.0f, -height / 2.0f, -width / 2.0f, -height / 2.0f, pos0) ||
				Intersect(0.0f, 0.0f, pos1.x, pos1.z, -width / 2.0f, -height / 2.0f, -width / 2.0f, height / 2.0f, pos0))
			{

			}
			else
			{																										   
				//int t = 0;
			}

			if (Intersect(0.0f, 0.0f, pos2.x, pos2.z, -width / 2.0f, height / 2.0f, width / 2.0f, height / 2.0f, pos3) ||
				Intersect(0.0f, 0.0f, pos2.x, pos2.z, width / 2.0f, height / 2.0f, width / 2.0f, -height / 2.0f, pos3) ||
				Intersect(0.0f, 0.0f, pos2.x, pos2.z, width / 2.0f, -height / 2.0f, -width / 2.0f, -height / 2.0f, pos3) ||
				Intersect(0.0f, 0.0f, pos2.x, pos2.z, -width / 2.0f, -height / 2.0f, -width / 2.0f, height / 2.0f, pos3))
			{

			}
			else
			{
				//int t = 0;
			}








			normal = (pos1 - pos0)*(pos3 - pos0);

			glNormal3d(normal.x, normal.y, normal.z);
			glVertex3d(pos0.x, pos0.y, pos0.z);
			glVertex3d(pos1.x, pos1.y, pos1.z);
			glVertex3d(pos2.x, pos2.y, pos2.z);			
			glVertex3d(pos3.x, pos3.y, pos3.z);
			pos0 = pos3;
			pos1 = pos2;
		}		 
		//pos0 = pos1;
		//pos1 = pos0 + Vector3(0.0f, 0.0f, w);
	}
	glEnd();

	glPopMatrix();
}