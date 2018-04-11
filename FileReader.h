#pragma once
#include "Model.h"
class FileReader
{
public:
	FileReader();
	~FileReader();
	void LoadRawFile(const char* fileName, const unsigned nSize, unsigned char* pHeightMap);
	void ReadModelOBJ(Model &model, const char *fileName);
	//int GetSceneNum(const char* fileName);
};