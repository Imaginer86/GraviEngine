#pragma once
#include <vector>
#include "Entity.h"

class Shape: public Entity
{
public:

	Shape(){};
	Shape(float32 m_, Vector3f pos_, Vector3f vel_, Math::Color4f color_);								// Constructor	

	virtual ~Shape();

	virtual void Init() {}
	virtual void Draw();

	void AddIndex(unsigned index_)
	{	
		//CoordIndex.resize(CoordIndex.size());
		std::vector<unsigned>& vector = CoordIndex[CoordIndex.size() - 1];
		vector.resize(vector.size());
		vector[vector.size() - 1] = index_;
	}

	void AddCoord(Vector3f& coord_)
	{
		//Coord.resize(Coord.size());
		std::vector<Vector3f>& vector = Coord[Coord.size() - 1];
		vector.resize(vector.size());
		vector[vector.size() - 1] = coord_;
	}

	void AddPart(unsigned numCoord_, unsigned numCoordIndex_)
	{
		Coord.resize(numCoord_);
		CoordIndex.resize(numCoordIndex_);
	}
	
	void SetNumPart(unsigned numPart)
	{
		Coord.resize(numPart);
		CoordIndex.resize(numPart);
	}

private:
	std::vector<std::vector<Vector3f>> Coord;
	std::vector<std::vector<unsigned>> CoordIndex;		
};

inline Shape::Shape(float32 m_, Vector3f pos_, Vector3f vel_, Math::Color4f color_)
: Entity(m_, pos_, vel_, color_)
//, numPart(numPart_)
//, Coord(nullptr)
//, NumCoord(nullptr)
//, CoordIndex(nullptr)
//, NumCoordIndex(nullptr)
{
}

inline Shape::~Shape()
{
	//for (std::list<Vector3f*>::iterator it = Coord.begin(); it != Coord.end(); ++it)
	//{
		//delete[] *it;
	//}
	//for (std::list<unsigned*>::iterator it = CoordIndex.begin(); it != CoordIndex.end(); ++it)
	//{
		//delete[] *it;
	//}
}