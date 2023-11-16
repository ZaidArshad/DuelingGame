#include "Model.h"
#include "OBJConstants.h"

#include "Helper/AppTools.h"
#include "Helper/Logger.h"
#include "Shader/Color.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <numeric>
#include <filesystem>

Model::Model(const std::string& dir)
{
	// Reading the obj files in the directory
	for (const auto& file : std::filesystem::directory_iterator(dir))
	{
		m_frames.push_back(parseOBJFile(file.path().string()));
	}
	
	if (m_frames.empty())
	{
		Logger::log("Could not read models from directory: " + dir + "\n");
	}

	m_frameIndex = 0;
	m_frameGap = 0;
}

Model::~Model()
{
	for (Frame* frame : m_frames)
	{
		delete frame;
	}
}

std::vector<float> Model::getTextureCoords()
{
	return m_frames[m_frameIndex]->vTextures;
}

std::vector<float> Model::getNormals()
{
	return m_frames[m_frameIndex]->vNormals;
}

void Model::updateModel()
{
	std::cout << m_frameIndex << std::endl;
	m_va.bind();
	m_va.updateBuffer(0, m_frames[m_frameIndex]->vPositions, GL_STREAM_DRAW);
	m_va.unbind();
}

void Model::nextFrame()
{
	if (m_frameGap == 5)
	{
		
		m_frameGap = 0;
		m_frameIndex = (m_frameIndex + 1) % m_frames.size();
		updateModel();
	}
	m_frameGap++;
}

void Model::resetFrames()
{
	m_frameIndex = 0;
	updateModel();
}

std::vector<float> Model::getPosition()
{
	return m_frames[m_frameIndex]->vPositions;
}

template <class T>
void printVectorVecs(std::vector<T>& outerVec, int length)
{
	for (auto& innerVec : outerVec)
	{
		for (int i = 0; i < length; i++)
		{
			std::cout << innerVec[i] << " ";
		}
		std::cout << std::endl;
	}
}

template <class T, class U>
void pushVecIntoVector(std::vector<T>& container, const U& vec, int length)
{
	for (int i = 0; i < length; i++)
	{
		container.push_back(vec[i]);
	}
}

Frame* Model::generateModel(std::vector<glm::vec3>& vPositions,
						  std::vector<glm::vec2>& vTextures,
						  std::vector<glm::vec3>& vNormals,
						  std::vector<Face>& faces)
{
	Frame* frame = new Frame();
	for (const Face& face : faces)
	{
		for (const auto& indices : face) // {v, vt, vn}
		{
			pushVecIntoVector(frame->vPositions, vPositions[indices[0]-1], 3);
			pushVecIntoVector(frame->vTextures, vTextures[indices[1]-1], 2);
			pushVecIntoVector(frame->vNormals, vNormals[indices[2]-1], 3);
		}
	}
	//AppTools::printVector(m_vPositions);
	//AppTools::printVector(m_vTextures);
	//AppTools::printVector(m_vNormals);
	if (m_frames.empty())
	{
		m_va.bind();
		m_vertCount = faces.size() * 3;
		m_va.addBuffer(frame->vPositions, 3);
		std::vector<float> colors;
		for (int i = 0; i < m_vertCount; i++)
		{
			colors.insert(colors.end(), COLOR_WHITE.begin(), COLOR_WHITE.end());
		}
		m_va.addBuffer(colors, 4);
		m_va.addBuffer(frame->vTextures, 2);

		// TODO Add normals to buffer

		std::vector<unsigned int> indices(m_vertCount);
		std::iota(indices.begin(), indices.end(), 0);
		m_va.setIndices(indices);
		m_va.unbind();
	}

	return frame;
}

Frame* Model::parseOBJFile(const std::string& path)
{
	std::cout << std::fixed << std::setprecision(6);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<Face> faces;

	std::ifstream stream(path);
	std::string line;
	std::string opcode;
	std::string payload;

	while (std::getline(stream, line))
	{
		std::stringstream buffer(line);
		buffer >> opcode;

		// Reading v
		if (opcode == STR_OBJ_VERTEX)
		{
			glm::vec3 vPosition;
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				vPosition[i] = std::stof(payload);
			}
			positions.push_back(vPosition);
		}
		// Reading vt
		else if (opcode == STR_OBJ_VERTEX_TEXTURE)
		{
			glm::vec2 vTexture;
			for (int i = 0; i < 2; i++)
			{
				buffer >> payload;
				vTexture[i] = std::stof(payload);
				
			}
			textures.push_back(vTexture);
		}
		// Reading vn
		else if (opcode == STR_OBJ_VERTEX_NORMAL)
		{
			glm::vec3 vNormal;
			for (int i = 0; i < 3; i++)
			{
				buffer >> payload;
				vNormal[i] = std::stof(payload);
			}
			normals.push_back(vNormal);
		}
		// Reading f
		else if (opcode == STR_OBJ_FACE)
		{
			Face face;
			for (int i = 0; i < 3; i++)
			{
				// Reading the indices for the faces (v/vt/vn)
				glm::ivec3 indices;
				buffer >> payload;
				std::stringstream faceBuffer(payload);
				for (int j = 0; j < 3; j++)
				{
					std::string val;
					std::getline(faceBuffer, val, '/');
					indices[j] = std::stoi(val);
				}
				face.push_back(indices);
			}
			faces.push_back(face);
		}
	}

	// Debug
	//std::cout << "Positions\n";
	//printVectorVecs(positions, 3);
	//std::cout << "Normals\n";
	//printVectorVecs(normals, 3);
	//std::cout << "Textures\n";
	//printVectorVecs(textures, 2);
	//std::cout << "Faces Indices\n";
	//for (auto face : faces)
	//{
	//	printVectorVecs(face, 3);
	//}
	// std::cout << std::endl;
	return generateModel(positions, textures, normals, faces);
} 
