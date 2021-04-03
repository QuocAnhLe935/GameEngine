#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_)
//						set to equal empty vector
	:VAO(0), VBO(0), vertexList(std::vector<Vertex>()), textureID(0), shaderProgram(0), viewLoc(0), projectionLoc(0), textureLoc(0)
{
	//setting the classes vertxlist vect= verList_ get pass in as parameter
	vertexList = vertexList_;
	textureID = textureID_;
	shaderProgram = shaderProgram_;
	GenerateBuffer();
}

Mesh::~Mesh()
{
	//OPENGL has its own way to delete VAO VBO
	//delete VAO
	glDeleteVertexArrays(1, &VAO);
	//delete VBO
	glDeleteBuffers(1, &VBO);

	//clear=hold not pointer object
	vertexList.clear();
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_)
{
	//assign unf varible to texture unit num 0
	glUniform1i(textureLoc, 0);
	//active texture num0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	

	//camera stuffs
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPosition()));
	
	//1st light
	glUniform1f(lightAmbient, camera_->get_light()[0]->getAmbient());
	glUniform1f(lightDiffuse, camera_->get_light()[0]->getDiffuse());
	glUniform1f(lightSpecular, camera_->get_light()[0]->getSpecular());
	glUniform3f(lightPos, camera_->get_light()[0]->getPosition().x, camera_->get_light()[0]->getPosition().y, camera_->get_light()[0]->getPosition().z);
	glUniform3f(lightColor, camera_->get_light()[0]->getLightColor().x, camera_->get_light()[0]->getLightColor().y, camera_->get_light()[0]->getLightColor().z);

	//2nd light
	/*glUniform1f(lightAmbient[1], camera_->get_light()[0]->getAmbient());
	glUniform1f(lightDiffuse[1], camera_->get_light()[0]->getDiffuse());
	glUniform1f(lightSpecular[1], camera_->get_light()[0]->getSpecular());
	glUniform3f(lightPos[1], camera_->get_light()[0]->getPosition().x, camera_->get_light()[0]->getPosition().y, camera_->get_light()[0]->getPosition().z);
	glUniform3f(lightColor[1], camera_->get_light()[0]->getLightColor().x, camera_->get_light()[0]->getLightColor().y, camera_->get_light()[0]->getLightColor().z);*/



	//bind VAO we want to use
	glBindVertexArray(VAO);

	//when the object is rendered, thier Z value will be taken into account
	glEnable(GL_DEPTH_TEST);

	//1p location of unif that want to set
	//2p how many varible, counts, uniform setting
	//3p want to transpose matrix? 4p ref/ptr to matrix
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_));

	//draw arrays
	//1p render type, 2p start element 0 (array), 3p end of array (how many object are you goin to draw)
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
	//glDrawArrays(GL_LINES, 0, vertexList.size());
	//clear vertex array for future use
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffer()
{
	//Create VAO & VBO to generate them by pass in the ref (&)
	//only making one of each (number 1)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO VBO to the GPU as an array buffer
	//opening a locker put a bunch of data (look the end) then close the door to that locker 
	glBindVertexArray(VAO);

	//VBO holds the datas, and VAO tell the GPU how the datas split up
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//	1para type of buffer 2para size of array
	//size of buffer multiply of each vertex elements
	//3rd para address of first item in array
	//4th para data will be only change once(static)
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex),
		&vertexList[0], GL_STATIC_DRAW);

	
	//Position
	
	glEnableVertexAttribArray(0);
	//tell gpu how things are sperated
	//1para Loc of attribute=0
	//2p size of vertex attribute(vec3) =3 types
	//3p this specific 3 float associate with it 
	//4p wheter we want to data want to be normalized
	//5p if have 3 verticles when Gpu look at pos to get pos to next
	//vertex you have to jump this much(sizxeof(vertex)
	//6p where data begin at the buffer 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	//6p offset: pass in the name of structure type, pass in(normal) the normal attribute that want offsetof
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

	//Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, textureCoordinates));

	//Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, color));


	//close the Locker nothing can screw around VAO VBO datas
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//get unilocation
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	
	cameraLoc = glGetUniformLocation(shaderProgram, "camera");

	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	lightColor = glGetUniformLocation(shaderProgram, "light.lightColor");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecular = glGetUniformLocation(shaderProgram, "light.specular");

	//lightPos[1] = glGetUniformLocation(shaderProgram, "light.lightPos[1]");
	//lightAmbient[1] = glGetUniformLocation(shaderProgram, "light.ambient[1]");
	//lightColor[1] = glGetUniformLocation(shaderProgram, "light.lightColor[1]");
	//lightDiffuse[1] = glGetUniformLocation(shaderProgram, "light.diffuse[1]");
	//lightSpecular[1] = glGetUniformLocation(shaderProgram, "light.specular[1]");
	
	
}
