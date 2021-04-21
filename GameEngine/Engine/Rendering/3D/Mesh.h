#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../FX/LightSource.h"
#include"../../Graphics/MaterialHandler.h"

#include"../../Core/Camera.h"
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	//what place on 2d image does this vertex take its textu info from
	glm::vec2 textureCoordinates;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned> meshIndices;
	//GLuint textureID;
	Material material;
	
};

class Mesh
{
public:
	//take vector of vertext objects -&pass by reference(address)
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	
	//set up VAO VBO
	void GenerateBuffer();
	//refer to week4.pdf
	GLuint VAO, VBO;
	std::vector<Vertex>vertexList;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc,  projectionLoc,  lightPos, lightAmbient, lightDiffuse, lightColor, lightSpecular, cameraLoc;
	GLuint diffuseMap, shininess, transparency, ambient, diffuse, specular;
};

#endif // !MESH_H
