#include "Shape.h"

#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../Math/Color.h"
#include "../Render/RenderGL.h"

using namespace Physics;

void Shape::Draw()
{
	glPushMatrix();
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(GetPos().x, GetPos().y, GetPos().z);

	
	for(unsigned i = 0; i < CoordIndex.size(); ++i)
	{
		for (unsigned j = 0; j < CoordIndex[i].size(); ++j)
		{
			Vector3f p1 = Coord[i][CoordIndex[i][j]];
			++j;
			Vector3f p2 = Coord[i][CoordIndex[i][j]];
			++j;
			Vector3f p3 = Coord[i][CoordIndex[i][j]];
			
			Render::RenderGL::Instance().DrawTriangle(p1, p2, p3, GetColor());
			//Render::RenderGL::Instance().DrawTriangle(p3, p4, p1, GetColor());
		}
	}

	glPopMatrix();
}