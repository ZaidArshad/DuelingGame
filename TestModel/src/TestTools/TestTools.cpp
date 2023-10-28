#include "TestTools.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<float> readVectorFile(const std::string& path)
{
	std::ifstream stream(path);
	std::string buffer;
	while (stream >> buffer)
	{
		std::cout << buffer << std::endl;
	}

	std::vector<float> vec;
	return vec;
}