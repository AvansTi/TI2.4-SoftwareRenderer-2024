#pragma once

#include <string>
#include <vector>
#include "Vec3.h"

struct Face
{
	int vertex[3];
	int normal[3];
};

class ObjModel
{
public:
	ObjModel(const std::string& fileName);


	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

};

