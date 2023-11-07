#include "TestTools.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<float> readVectorFile(const std::string& path)
{
	std::ifstream stream(path);
	std::string buffer;
	std::vector<float> vec;
	while (stream >> buffer)
	{
		vec.push_back(std::stof(buffer));
	}
	
	return vec;
}