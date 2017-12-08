#pragma once

class Tera
{
public:
	static const int MAP_SIZE = 1024;
	static const int STEP_SIZE = 32;
	unsigned char HeightMap[MAP_SIZE*MAP_SIZE];
	int Height(int x, int y) const;
};

inline int Tera::Height(int X, int Y) const
{
	unsigned x = X % MAP_SIZE;
	unsigned y = Y % MAP_SIZE;

	if (!HeightMap) 
		return 0;

	return static_cast<int>(HeightMap[x + (y * MAP_SIZE)]);
}
