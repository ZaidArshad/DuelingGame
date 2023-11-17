#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid(float length);
	~Pyramid();

	// -- Utility -- //
	std::vector<float> getPosition();

private:
	float m_length;
};

