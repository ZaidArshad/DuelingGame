#pragma once
class Shape
{
public:
	virtual void draw() = 0;
	virtual glm::mat4 getModelMatrix() = 0;
};