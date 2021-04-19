#ifndef  LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include"Mesh.h"
#include <sstream>
#include"../../Graphics/TextureHandler.h"
#include"../../FX/MaterialLoader.h"


class LoadOBJmodel
{
public:
	LoadOBJmodel();
	~LoadOBJmodel();

	void LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_);
	std::vector<SubMesh> GetSubMeshes();

private:
	void PostProcessing();
	void LoadModel(const std::string& filePath_);
	void LoadMaterial(const std::string& matName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<unsigned int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> submeshs;
	//GLuint currentTexture;

	Material currentMaterial;
};

#endif // ! LOADOBJMODEL_H
