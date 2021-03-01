#include "Model.h"
//set meshe vector to empty vector
	


Model::Model(GLuint shaderProgram_, glm::vec3 poistion_, glm::vec3 rotation_, glm::vec3 scale_, float angle_)
{
	shaderProgram = 0;
	shaderProgram = shaderProgram_;

	position = glm::vec3();
	position = poistion_;

	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	rotation = rotation_;

	scale = glm::vec3(1.0f);
	scale = scale_;

	angle = 0.0f;
	angle = angle_;

	meshes = std::vector<Mesh*>();

}

Model::~Model()
{
	//go to each elements of vector and delete them
	//Has sth in it
	if (meshes.size() > 0) {
		//create tmp varible for each element
		//auto automatic set type of this varible	
		//: ==in

		//for each element m in(:) this mesh vector
		for (auto m : meshes) {
			delete m; 
			m = nullptr;
		}
		//allocate mesh or memory leaks
		meshes.clear();
	}
}

void Model::Render(Camera* camera_)
{
	//tell opengl to switch shader pro to specifi shader pro we are passing it
	glUseProgram(shaderProgram);
	//for each mesh in meshes list call render on it
	for (auto m : meshes) {
		m->Render(camera_, GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	//add a mesh to meshes vector
	meshes.push_back(mesh_);
}

glm::vec3 Model::GetPosition() const
{
	return position;
}

glm::vec3 Model::GetRotation() const
{
	return rotation;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

float Model::GetAngle() const
{
	return angle;
}

void Model::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(glm::vec3 scale_)
{
	scale = scale_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}


//create model matrix
glm::mat4 Model::GetTransform() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	

	return model;
}
