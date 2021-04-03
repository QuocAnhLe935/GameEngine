#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../FX/LightSource.h"


#include"../../Core/Camera.h"
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	//what place on 2d image does this vertex take its textu info from
	glm::vec2 textureCoordinates;
	glm::vec3 color;
	
	
};
class Mesh
{
public:
	//take vector of vertext objects -&pass by reference(address)
	Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_,GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, glm::mat4 transform_);

private:
	
	//set up VAO VBO
	void GenerateBuffer();
	//refer to week4.pdf
	GLuint VAO, VBO;
	std::vector<Vertex>vertexList;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc,  projectionLoc, textureLoc, lightPos, lightAmbient, lightDiffuse, lightColor, lightSpecular, cameraLoc;
};

#endif // !MESH_H
