#pragma once
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid(float length);
	~Pyramid();
	void setTexture(const std::string& path);

	// Overloaded virtual functions of Shape
	std::vector<float> getPosition() override;

private:
	float m_length;
};

