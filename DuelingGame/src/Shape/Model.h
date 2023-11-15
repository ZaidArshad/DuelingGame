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
	// Takes in a directory of obj files
	Model(const std::string& dir);
	~Model();

	// -- Getters -- //
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();

	// -- Utility -- //
	void updateModel();
	void nextFrame();
	void resetFrames();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	Frame* generateModel(std::vector<glm::vec3>& vPositions,
					   std::vector<glm::vec2>& vTextures,
					   std::vector<glm::vec3>& vNormals,
					   std::vector<Face>& faces);
	Frame* parseOBJFile(const std::string& path);

	// One frame for each model loaded
	Frames m_frames;
	unsigned int m_frameIndex;

	std::vector<float> m_vPositions;

	unsigned int m_frameGap;
};

