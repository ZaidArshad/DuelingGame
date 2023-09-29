#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid(float length);
	~Pyramid();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	float m_length;
};

