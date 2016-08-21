#pragma once
#include <vector>
#include "Entity.h"

namespace Physics
{

class Shape: public Entity
{
public:

	Shape(){};
	Shape(float m_, Math::Vector3f pos_, Math::Vector3f vel_, Math::Color4f color_);								// Constructor	

	virtual ~Shape(){}

	virtual void Init() {}
	virtual void Draw();

	void AddIndex(unsigned index_)
	{	
		CoordIndex.back().push_back(index_);
		//std::vector<unsigned>& vector = CoordIndex[CoordIndex.size() - 1];
		//vector.resize(vector.size());
		//vector[vector.size() - 1] = index_;
	}

	void AddCoord(Math::Vector3f& coord_)
	{
		Coord.back().push_back(coord_);
		//std::vector<Vector3f>& vector = Coord[Coord.size() - 1];
		//vector.resize(vector.size());
		//vector[vector.size() - 1] = coord_;
	}

	void AddPart(/*unsigned numCoord_, unsigned numCoordIndex_*/)
	{
		//Coord.resize(numCoord_);
		//CoordIndex.resize(numCoordIndex_);
		std::vector<Math::Vector3f> coord;
		Coord.push_back(coord);
		std::vector<unsigned> coordIndex;
		CoordIndex.push_back(coordIndex);
	}
	
	void SetNumPart(unsigned numPart)
	{
		Coord.resize(numPart);
		CoordIndex.resize(numPart);
	}

private:
	std::vector<std::vector<Math::Vector3f>> Coord;
	std::vector<std::vector<unsigned>> CoordIndex;		
};

inline Shape::Shape(float m_, Math::Vector3f pos_, Math::Vector3f vel_, Math::Color4f color_)
: Entity(m_, pos_, vel_, color_)
//, numPart(numPart_)
//, Coord(nullptr)
//, NumCoord(nullptr)
//, CoordIndex(nullptr)
//, NumCoordIndex(nullptr)
{
}

}