#pragma once
#include <vector>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;
class Model
{
public:
	/*  函数   */
	Model(char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  模型数据  */
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	/*  函数   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};