#include "WaveOut.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

using namespace Math;
using namespace Physics;

bool Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Vector3f& pos)
{
//	float ua = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float ub = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

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

	float hangle = 360.0f/float(numRo);

	glBegin(GL_QUADS);       // Начало рисования четырехугольников

	glColor4f(color.r, color.g, color.b, color.a);

	Vector3f pos0, pos1, pos2, pos3;
	Vector3f normal;

	//pos0 = pos;
	//pos1 = pos0 + Vector3(0.0f, 0.0f, w);

	unsigned r = numR;
	{
		for (unsigned ro = 0; ro < numRo /2; ro++)
		{
			float angle0 = degreesToRadians(hangle*float(ro));
			float angle1 = degreesToRadians(hangle*float(ro + 1));
			//float dist0 = r*w;
			float dist1 = (r + 1)*w;

			//pos0 = Vector3(dist0*cosf(angle0), 0.0f, dist0*sinf(angle0));
			pos1 = Vector3f(dist1*cos(angle0), 0.0f, dist1*sin(angle0));
			pos2 = Vector3f(dist1*cos(angle1), 0.0f, dist1*sin(angle1));
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