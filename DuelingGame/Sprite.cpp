#include "Sprite.h"
#include "AppTools.h"
#include <GLFW/glfw3.h>

Sprite::Sprite(double x, double y, double w, double h)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
}

void Sprite::drawBox()
{
	double left = AppTools::normalizeX(xPos);
	double right = AppTools::normalizeX(xPos+width);
	double top = AppTools::normalizeY(yPos);
	double bottom = AppTools::normalizeY(yPos+height);
	glBegin(GL_QUAD_STRIP);
	glVertex2d(left, top);
	glVertex2d(right, top);
	glVertex2d(left, bottom);
	glVertex2d(right, bottom);
	glEnd();
}


void Sprite::setPosition(double x, double y)
{
	xPos = x;
	yPos = y;
}