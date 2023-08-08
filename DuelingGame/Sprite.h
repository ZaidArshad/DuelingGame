#pragma once
class Sprite
{
private:
	double xPos;
	double yPos;
	double width;
	double height;
public:
	Sprite(double x, double y, double w, double h);
	void drawBox();
	void setPosition(double x, double y);
};

