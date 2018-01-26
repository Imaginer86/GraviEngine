#pragma once
#include <string>
#include "Vector3f.h"

class Surface
{
public:
	size_t n;
	size_t *Vertexs;
	size_t *Normals;

	Surface():n(0), Vertexs(nullptr), Normals(nullptr) {};
	Surface(const Surface &surface)
	{
		n = surface.n;
		Vertexs = new size_t[n];
		Normals = new size_t[n];
		for (size_t i = 0; i < n; ++i)
		{
			Vertexs[i] = surface.Vertexs[i];
			Normals[i] = surface.Normals[i];
		}
	}
	Surface & operator=(const Surface &surface)
	{
		if (this != &surface)
		{
			if (Vertexs) delete[] Vertexs;
			if (Normals) delete[] Normals;
			n = surface.n;
			Vertexs = new size_t[n];
			Normals = new size_t[n];
			for (size_t i = 0; i < n; ++i)
			{
				Vertexs[i] = surface.Vertexs[i];
				Normals[i] = surface.Normals[i];
			}
		}
		return *this;
	}
	~Surface() { if(Vertexs) delete[] Vertexs; if (Normals) delete[] Normals; }
};
class Group
{
public:
	std::string name;
	size_t size;
	Surface *surfaces;
public:
	Group():size(0), surfaces(nullptr) {};
	Group(const Group &group)
	{
		name = group.name;
		size = group.size;
		surfaces = new Surface[size];
		for (size_t i = 0; i < size; ++i)
		{
			surfaces[i] = group.surfaces[i];
		}
	}
	Group & operator=(const Group &group)
	{
		if (this != &group)
		{
			name = group.name;
			size = group.size;
			surfaces = new Surface[size];
			for (size_t i = 0; i < size; ++i)
			{
				surfaces[i] = group.surfaces[i];
			}
		}
		return *this;
	}
	~Group() { if(surfaces) delete[] surfaces; }
};

class Model
{
public:

public:
	Vector3f *vertexs;
	Vector3f *normals;
	size_t nVertex;
	size_t nNormal;

	size_t nGroup;
	Group *groups;
public:
	Model();
	~Model();
	void setSizeGroup(size_t n);
	void setSizeVertex(size_t n);
	void setSizeNormal(size_t n);

	//void Draw();
};

