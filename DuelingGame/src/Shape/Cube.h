#pragma once
#include "Shape.h"
class Cube : public Shape
{
public:
	Cube();
	Cube(float length);
	~Cube();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	float m_length;
};

