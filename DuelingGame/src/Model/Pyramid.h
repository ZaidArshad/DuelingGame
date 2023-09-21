#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid(float x, float y, float z, float length);
	~Pyramid();
	void rotateModelX(float radians);

	// Overloaded virtual functions of Shape
	void draw() override;
	std::vector<float> getPosition() override;

private:
	float m_x;
	float m_y;
	float m_z;
	float m_length;
};

