#include "Model.h"
//set meshe vector to empty vector
Model::Model(GLuint shaderProgram_) :meshes(std::vector<Mesh*>()), shaderProgram(0)
{
	shaderProgram = shaderProgram_;
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

void Model::Render()
{
	//tell opengl to switch shader pro to specifi shader pro we are passing it
	glUseProgram(shaderProgram);
	//for each mesh in meshes list call render on it
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	//add a mesh to meshes vector
	meshes.push_back(mesh_);
}
