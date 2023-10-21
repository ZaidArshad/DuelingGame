#pragma once
#include "Shape.h"

class Model : public Shape
{
public:
	Model(const std::string& path);
	~Model();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	void parseOBJFile(const std::string& path);
};

