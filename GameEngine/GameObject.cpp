#include "GameObject.h"

//make sure there is no junk data(model=nullptr)
GameObject::GameObject(Model* model_): model(nullptr)
{
	model = model_;
}

GameObject::~GameObject()
{
	//why model=nullptr outside of if
	//want engine have ability to have empty game object
	if (model) {
		delete model;
	}
	model = nullptr;
}

void GameObject::Render()
{
	//if there is model then render 
	if (model) {
		printf("MODEL");
		model->Render();
	}
}
