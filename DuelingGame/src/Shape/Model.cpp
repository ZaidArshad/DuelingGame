#include "Model.h"

#include<iostream>
#include <iomanip>
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
	std::vector<std::vector<int>> faces;

	std::ifstream stream(path);
	std::string line;
	std::string opcode;
	std::string payload;

	while (std::getline(stream, line))
	{
		std::stringstream buffer(line);
		buffer >> opcode;

		if (opcode == "v")
		{
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				positions.push_back(std::stof(payload));
			}
			
		}
		else if (opcode == "vt")
		{
			for (int i = 0; i < 2; i++)
			{
				buffer >> payload;
				textures.push_back(std::stof(payload));
			}
		}
		else if (opcode == "vn")
		{
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				normals.push_back(std::stof(payload));
			}
		}
		else if (opcode == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				std::vector<int> face;
				buffer >> payload;
				std::stringstream faceBuffer(payload);
				for (int j = 0; j < 3; j++)
				{
					std::string val;
					std::getline(faceBuffer, val, '/');
					face.push_back(std::stoi(val));
				}
				faces.push_back(face);
			}
		}
	}
}
