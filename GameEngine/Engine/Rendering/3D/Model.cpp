#include "Model.h"
//set meshe vector to empty vector
	


Model::Model(GLuint shaderProgram_, const std::string& objPath_, const std::string& matPath_)
{
	shaderProgram = 0;
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstance.reserve(5);
	modelInstance = std::vector<glm::mat4>();
	meshes = std::vector<Mesh*>();
	obj = nullptr;

	obj = new LoadOBJmodel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();

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
	if (modelInstance.size() > 0) {
		modelInstance.clear();
	}
}

void Model::Render(Camera* camera_)
{
	//tell opengl to switch shader pro to specifi shader pro we are passing it
	glUseProgram(shaderProgram);
	//for each mesh in meshes list call render on it
	for (auto m : meshes) {
		m->Render(camera_, modelInstance);
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	//add a mesh to meshes vector
	meshes.push_back(mesh_);
	
}


unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstance.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstance.size() - 1;
}

void Model::UpdateInstance(unsigned int index, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	//get specific model matrix
	modelInstance[index] = CreateTransform(position_, angle_, rotation_, scale_);
}

//using model instance varible (unsgine int) 
glm::mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstance[index_];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

BoundingBox Model::GetBoundingBox() const
{
	return boundingbox;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		meshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	boundingbox = obj->GetBoundingBox();
	
	delete obj;
	obj = nullptr;
}



