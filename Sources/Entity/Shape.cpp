#include "Shape.h"

#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../Math/Color.h"
#include "../Render/RenderGL.h"

void Shape::Draw()
{

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	currentPart = 0;

	CurrentCoord = 0;

	CurrentCoordIndex = 0;
	
	for(currentPart; currentPart < numPart; currentPart++)
	{
		for(unsigned j = 0;  j  < NumCoordIndex[currentPart];)
		{

			Vector3f p1 = Coord[currentPart][CoordIndex[currentPart][CurrentCoordIndex]];
			++CurrentCoord; ++CurrentCoordIndex; ++j;
			Vector3f p2 = Coord[currentPart][CoordIndex[currentPart][CurrentCoordIndex]];
			++CurrentCoord; ++CurrentCoordIndex; ++j;
			Vector3f p3 = Coord[currentPart][CoordIndex[currentPart][CurrentCoordIndex]];
			++CurrentCoord; ++CurrentCoordIndex; ++j;

			//Vector3f p1 = Coord[currentPart][CoordIndex[currentPart][j]]; ++j;
			//Vector3f p2 = Coord[currentPart][CoordIndex[currentPart][j]]; ++j;
			//Vector3f p3 = Coord[currentPart][CoordIndex[currentPart][j]]; ++j;
			
			Render::RenderGL::Instance().DrawTriangle(p1, p2, p3, Math::Color4f(0.5f, 0.5f, 0.5f, 0.75f));
		}

	CurrentCoord = 0;
	CurrentCoordIndex = 0;

	}
}