#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid(float length);
	~Pyramid();
	void setTexture(const std::string& path);
	void translate(float x, float y, float z);
	void rotateModelX(float radians);

	// Overloaded virtual functions of Shape
	void draw() override;
	std::vector<float> getPosition() override;

private:
	float m_length;
};

