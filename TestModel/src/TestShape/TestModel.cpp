#include "TestShape.h"
#include "Shape/Model.h"
#include "TestTools/TestTools.h"
#include <iostream>

void testModel()
{
	Model model("res/Models/cube/cube.obj");
	assert("Failed reading position coordiantes" && 
			readVectorFile("res/Models/cube/verification/positions.txt") == model.getPosition());
	assert("Failed reading normal coordiantes" &&
		    readVectorFile("res/Models/cube/verification/normals.txt") == model.getNormals());
	assert("Failed reading texture coordiantes" &&
		    readVectorFile("res/Models/cube/verification/textures.txt") == model.getTextureCoords());
}