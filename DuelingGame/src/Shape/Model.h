#pragma once
#include "Shape.h"

typedef std::vector<glm::ivec3> Face;

class Model : public Shape
{
public:
	Model(const std::string& path);
	~Model();

	// -- Overload -- //
	std::vector<float> getPosition() override;

private:
	void generateModel(std::vector<glm::vec3>& vPositions,
					   std::vector<glm::vec2>& vTextures,
					   std::vector<glm::vec3>& vNormals,
					   std::vector<Face>& faces);
	void parseOBJFile(const std::string& path);

	std::vector<float> m_vPositions;
	std::vector<float> m_vTextures;
	std::vector<float> m_vNormals;

};

