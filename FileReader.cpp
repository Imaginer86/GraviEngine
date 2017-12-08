#include <string>
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

void FileReader::ReadModelOBJ(Model &model, const char *fileName)
{
	list<Vector3f> lVertexs;
	list<Vector3f> lNormals;
	list<Group> lGroups;
	list<Surface> lSurface;
	

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
			char ch = sstr.peek();
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
			surface.Vertexs = new size_t[surface.n];
			surface.Normals = new size_t[surface.n];

			size_t i = 0;
			for (auto it : vert)
			{
				surface.Vertexs[i] = it;
				++i;
			}

			i = 0;
			for (auto it : norm)
			{
				surface.Normals[i] = it;
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
				for (auto it : lSurface)
				{
					group.surfaces[i].n = it.n;
					group.surfaces[i] = it;
					++i;
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
	for (auto it : lVertexs)
	{
		model.vertexs[i] = it;
		++i;
	}
	lVertexs.clear();

	n = lNormals.size();
	model.setSizeNormal(n);;
	i = 0;
	for (auto it : lNormals)
	{
		model.normals[i] = it;
		++i;
	}
	lNormals.clear();

	n = lGroups.size();
	model.setSizeGroup(n);
	i = 0;
	for (auto it : lGroups)
	{
		model.groups[i] = it;
		++i;
	}
	lGroups.clear();

}
