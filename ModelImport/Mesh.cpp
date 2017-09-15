#include "Mesh.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
Mesh::Mesh(std::vector<Vertex> vertexs, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertexs = vertexs;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0;i < textures.size();++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // 将 unsigned int 插入到流中
		else if (name == "texture_specular")
			ss << specularNr++; // 将 unsigned int 插入到流中
		number = ss.str();

		shader.setFloat(("material." + name + number).c_str(), i);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(Vertex), &vertexs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,TexCoords)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);

}
