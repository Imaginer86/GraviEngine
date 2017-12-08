#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
	delete[] groups;
	delete[] vertexs;
	delete[] normals;
}

void Model::setSizeGroup(size_t n)
{
	nGroup = n;
	groups = new Group[nGroup];
}

void Model::setSizeVertex(size_t n)
{
	nVertex = n;
	vertexs = new Vector3f[nVertex];
}

void Model::setSizeNormal(size_t n)
{
	nNormal = n;
	normals = new Vector3f[nNormal];
}
