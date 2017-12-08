#pragma once
#include "Model.h"
class FileReader
{
public:
	FileReader();
	~FileReader();
	void ReadModelOBJ(Model &model, const char *fileName);
};

