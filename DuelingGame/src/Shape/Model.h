#pragma once
#include "Shape.h"

typedef std::vector<glm::ivec3> Face;

struct Frame
{
	std::vector<float> vPositions;
	std::vector<float> vTextures;
	std::vector<float> vNormals;
};

typedef std::vector<Frame*> Frames;

class Model : public Shape
{
public:
	Model(const std::string& path);
	~Model();

	// -- Getters -- //
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	Frame* generateModel(std::vector<glm::vec3>& vPositions,
					   std::vector<glm::vec2>& vTextures,
					   std::vector<glm::vec3>& vNormals,
					   std::vector<Face>& faces);
	Frame* parseOBJFiles(const std::string& dir);

	// One frame for each model loaded
	Frames m_frames;
};

