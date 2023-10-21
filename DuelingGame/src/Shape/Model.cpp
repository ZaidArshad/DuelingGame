#include "Model.h"
#include "OBJConstants.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>

Model::Model(const std::string& path)
{
	parseOBJFile(path);
}

Model::~Model()
{
}

std::vector<float> Model::getPosition()
{
	return std::vector<float>();
}

void Model::parseOBJFile(const std::string& path)
{
	std::cout << std::fixed << std::setprecision(6);

	std::vector<float> positions;
	std::vector<float> textures;
	std::vector<float> normals;
	std::vector<std::vector<std::vector<int>>> faces;

	std::ifstream stream(path);
	std::string line;
	std::string opcode;
	std::string payload;

	while (std::getline(stream, line))
	{
		std::stringstream buffer(line);
		buffer >> opcode;

		if (opcode == STR_OBJ_VERTEX)
		{
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				positions.push_back(std::stof(payload));
			}
			
		}
		else if (opcode == STR_OBJ_VERTEX_TEXTURE)
		{
			for (int i = 0; i < 2; i++)
			{
				buffer >> payload;
				textures.push_back(std::stof(payload));
			}
		}
		else if (opcode == STR_OBJ_VERTEX_NORMAL)
		{
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				normals.push_back(std::stof(payload));
			}
		}
		else if (opcode == STR_OBJ_FACE)
		{
			std::vector<std::vector<int>> face;
			for (int i = 0; i < 3; i++)
			{
				std::vector<int> indices;
				buffer >> payload;
				std::stringstream faceBuffer(payload);
				for (int j = 0; j < 3; j++)
				{
					std::string val;
					std::getline(faceBuffer, val, '/');
					indices.push_back(std::stoi(val));
				}
				face.push_back(indices);
			}
			faces.push_back(face);
		}
	}
}
