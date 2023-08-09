#pragma once
class Box
{
private:
	double xPos;
	double yPos;
	double width;
	double height;
public:
	Box(double x, double y, double w, double h);
	void drawBox();
	void setPosition(double x, double y);
};

