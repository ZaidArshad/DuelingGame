#pragma once
#include "Shape.h"

typedef std::vector<glm::ivec3> Face;

struct Frame
{
	std::vector<float> vPositions;
	std::vector<float> vTextures;
	std::vector<float> vNormals;
};

class Model : public Shape
{
public:
	// Takes in a directory of obj files
	Model(const std::string& dir);
	~Model();

	// -- Utility -- //
	void nextFrame();
	void resetFrames();

	// -- Overload -- //
	void draw() override;

private:
	void generateModel(std::vector<glm::vec3>& vPositions,
					   std::vector<glm::vec2>& vTextures,
					   std::vector<glm::vec3>& vNormals,
					   std::vector<Face>& faces);
	void parseOBJFile(const std::string& path);

	// One frame for each model loaded
	std::vector<VertexArray*> m_vaFrames;
	unsigned int m_frameIndex;
	unsigned int m_frameGap;
};

