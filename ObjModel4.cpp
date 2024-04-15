#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <sstream>


ObjModel::ObjModel(const std::string& fileName)
{
	std::ifstream file(fileName);
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);


		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			continue;
//		std::cout << line << std::endl;
		
		std::stringstream lineStream(line);

		std::string command;
		lineStream >> command;
		if (command == "v")
		{
			Vec3 vertex;
			for(int i = 0; i< 3; i++)
				lineStream >> vertex.data[i];
			vertices.push_back(vertex);
		}
		else if (command == "vt" || command == "s" || command == "o")
			continue;
		else if (command == "vn")
		{
			Vec3 normal;
			for (int i = 0; i < 3; i++)
				lineStream >> normal.data[i];
			normals.push_back(normal);
		}
		else if (command == "f")
		{
			Face face;
			char junk;
			for (int f = 0; f < 3; f++) //TODO: not every face has 3 vertices
			{
				lineStream >> face.vertex[f];
				lineStream >> junk;
				int tex;
				lineStream >> tex;
				lineStream >> junk;
				lineStream >> face.normal[f];
			}
			faces.push_back(face);
		}
		else
			std::cout << "Unknown segment in obj file" << command << std::endl;

	}


}
