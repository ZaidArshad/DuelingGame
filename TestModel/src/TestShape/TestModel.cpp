#include "TestShape.h"
#include "Shape/Model.h"
#include "TestTools/TestTools.h"


void testModel()
{
	Model model("res/Models/cube/cube.obj");
	readVectorFile("res/Models/cube/vertexData.txt");
}