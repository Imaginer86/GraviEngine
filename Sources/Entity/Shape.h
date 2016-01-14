#pragma once
#include "Entity.h"

class Shape: public Entity
{
public:

	Shape();
	Shape(float32 m_, Vector3f pos_, Vector3f vel_, Math::Color4f color_, unsigned numPart_);								// Constructor	

	virtual ~Shape();

	void Init(unsigned numPart_)
	{
		numPart = numPart_;
		Coord = new Vector3f*[numPart];
		NumCoord = new unsigned[numPart];
		CurrentCoord = 0;
		CoordIndex = new unsigned*[numPart];
		NumCoordIndex = new unsigned[numPart];
		CurrentCoordIndex = 0;
	}

	void AddIndex(unsigned index_)
	{
		CoordIndex[currentPart-1][CurrentCoordIndex] = index_;
		++CurrentCoordIndex;
	}

	void AddCoord(const Vector3f& coord_)
	{
		Coord[currentPart-1][CurrentCoord] = coord_;
		++CurrentCoord;
	}

	void AddPart(unsigned numCoord_, unsigned numCoordIndex_)
	{
		Coord[currentPart] = new Vector3f[numCoord_];
		NumCoord[currentPart] = numCoord_;
		CurrentCoord = 0;
		
		CoordIndex[currentPart] = new unsigned[numCoordIndex_];
		NumCoordIndex[currentPart] = numCoordIndex_;
		CurrentCoordIndex = 0;
				
		++currentPart;		
	}
	
	virtual void Draw();

	void SetCurrentPart(unsigned currentPart_)
	{
		currentPart = currentPart_;
	}

private:
	unsigned currentPart;
	unsigned numPart;
	Vector3f** Coord;
	unsigned* NumCoord;
	unsigned CurrentCoord;
	unsigned** CoordIndex;
	unsigned* NumCoordIndex;
	unsigned CurrentCoordIndex;
		
};

inline Shape::Shape()
: Entity()
, currentPart(0)
, numPart(0)
, Coord(nullptr)
, NumCoord(nullptr)
, CoordIndex(nullptr)
, NumCoordIndex(nullptr)
{
}


inline Shape::Shape(float32 m_, Vector3f pos_, Vector3f vel_, Math::Color4f color_, unsigned numPart_)
: Entity(m_, pos_, vel_, color_)
, currentPart(0)
, numPart(numPart_)
, Coord(nullptr)
, NumCoord(nullptr)
, CoordIndex(nullptr)
, NumCoordIndex(nullptr)
{
}

inline Shape::~Shape()
{
	for (unsigned i = 0; i < numPart; i++)
	{
		delete[] Coord[i];
		delete[] CoordIndex[i];
	}
	delete[] NumCoord;
	delete[] NumCoordIndex;
	numPart = 0;

}