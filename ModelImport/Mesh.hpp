#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "assimp/types.h"
#include "shader.hpp"
struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

};

struct Texture
{	
	unsigned int id;
	std::string type;
	aiString path;  // 我们储存纹理的路径用于与其它纹理进行比较
};


class Mesh {

public:
	std::vector<Vertex> vertexs;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertexs, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void draw(Shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};