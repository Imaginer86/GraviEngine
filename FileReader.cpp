#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#include "FileReader.h"

using namespace std;

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

void FileReader::LoadRawFile(const char * fileName, const unsigned nSize, unsigned char * pHeightMap)
{
	//#ifdef _WIN32
	//FILE *pFile = NULL;
	//#else
	//char *pFIle;
	//#endif

	fstream in;
	in.open(fileName);

	// �������� ����� � ������ ��������� ������
	//fopen(&pFIle, fileName, "rb");

	// ���� ������?
	if (!in.is_open())
	{
		// ������� ��������� �� ������ � ������� �� ���������
		cerr << "Can't Find The Height Map!" << std::endl; //MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		return;
	}

	// ��������� .RAW ���� � ������ pHeightMap
	// ������ ��� ������ �� ������ �����, ������ = ������ * ������
	//fread(pHeightMap, 1, nSize, in);
	//todo

	// ��������� �� ������� ������
	//int result = ferror(in);
	
	// ���� ��������� ������
	if (in.eof())
	{
		std::cerr << "Failed To Get Data!" << std::endl;// (NULL, "Failed To Get Data!", "Error", MB_OK);
	}
	// ��������� ����
	in.close();
}

void FileReader::ReadModelOBJ(Model &model, const char *fileName)
{
	std::list<Vector3f> lVertexs;
	std::list<Vector3f> lNormals;
	std::list<Group> lGroups;
	std::list<Surface> lSurface;
	

	ifstream infile;
	infile.open(fileName, ios::in);

	if (!infile) return;

	bool bSurface = false;
	bool bf = false;
	while (!infile.eof())
	{
		string line;
		getline(infile, line);
		stringstream sstr;
		sstr << line;
		std::string str;
		char c;
		sstr >> c;
		switch (c)
		{
		case '#':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;			
			lGroups.push_back(group);
			break;
		}
		case 'm':
		{
			sstr >> str;
			if (str == "tllib")
			{
				sstr >> str;
			}
			break;
		}
		case 'v':
		{
			char ch = static_cast<char>(sstr.peek());
			if (ch == 'n')
			{
				sstr >> ch;
				Vector3f n;
				sstr >> n.x >> n.y >> n.z;
				lNormals.push_back(n);
			}
			else if (ch == 't')
			{
				continue;
			}
			else
			{
				Vector3f v;
				sstr >> v.x >> v.y >> v.z;
				lVertexs.push_back(v);
			}
			break;
		}
		case 'g':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;
			sstr >> group.name;
			lGroups.push_back(group);
			break;
		}
		case 'o':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;
			sstr >> group.name;
			lGroups.push_back(group);
			break;
		}
		case 'u':
		{
			sstr >> str;
			if (str == "semtl")
			{

			}
			break;
		}
		case 's':
		{
			break;
		}
		case 'f':
		{
			bf = true;			
			Surface surface;
			list<size_t> vert;
			list<size_t> norm;
			unsigned v, t, n;
			char ch;
			bool finish = false;
			while ( !finish && !sstr.eof())
			{
				finish = false;
				sstr >> v;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> ch;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> t;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> ch;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> n;				
				--v; --n;
				vert.push_back(static_cast<size_t>(v));
				norm.push_back(static_cast<size_t>(n));
			}
			surface.n = vert.size();
			if (surface.n == 5)
			{
				int tt = 0;
			}
			surface.Vertexs = new size_t[surface.n];
			surface.Normals = new size_t[surface.n];

			size_t i = 0;
			for (std::list<size_t>::iterator it = vert.begin(); it != vert.end(); ++it)
			{
				surface.Vertexs[i] = *it;
				++i;
			}

			i = 0;
			for (std::list<size_t>::iterator it = norm.begin(); it != norm.end(); ++it)
			{
				surface.Normals[i] = *it;
				++i;
			}
			
			lSurface.push_back(surface);

			break;
		}
		default:
		{

		}
		}

		if (!lGroups.empty())
		{
			Group groupEnd;
			groupEnd = lGroups.back();
			lGroups.pop_back();

			if (bSurface && !lSurface.empty())
			{
				bSurface = false;
				

				Group group;
				group = lGroups.back();
				lGroups.pop_back();
				group.size = lSurface.size();
				group.surfaces = new Surface[group.size];

				size_t i = 0;

				for (std::list<Surface>::iterator it = lSurface.begin(); it != lSurface.end(); ++it, ++i)
				{
					//group.surfaces[i].n = *it.n;
					group.surfaces[i] = *it;
				}
				lGroups.push_back(group);
				lSurface.clear();
			}

			lGroups.push_back(groupEnd);
		}
	}

	infile.close();
	lGroups.pop_back();

	size_t n = lVertexs.size();
	model.setSizeVertex(n);
	
	size_t i = 0;
	for (std::list<Vector3f>::iterator it = lVertexs.begin(); it != lVertexs.end(); ++it, ++i)
	{
		model.vertexs[i] = *it;
	}
	lVertexs.clear();

	model.setSizeNormal(n);
	i = 0;
	for(std::list<Vector3f>::iterator it = lNormals.begin(); it != lNormals.end(); ++it, ++i)
	{
		model.normals[i] = *it;
	}
	lNormals.clear();

	model.setSizeGroup(n);
	i = 0;
	for(std::list<Group>::iterator it = lGroups.begin(); it != lGroups.end(); ++it, ++i)
	{
		model.groups[i] = *it;		
	}
	lGroups.clear();

}

//int FileReader::GetSceneNum(const char * fileName)
//{
	//ifstream inFile;
	//inFile.open(fileName, ios::in);
	//string str;
	//inFile >> str;
	//int res = 0;
	//if (str == "scene")	inFile >> res;
	//return res;
	//return 0;
//}
