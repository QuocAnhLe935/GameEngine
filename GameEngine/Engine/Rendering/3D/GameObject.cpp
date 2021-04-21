#include "GameObject.h"

//make sure there is no junk data(model=nullptr)
//GameObject::GameObject(Model* model_): model(nullptr)
//{
//	position = glm::vec3();
//	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
//	scale = glm::vec3(1.0f);
//	angle = 0.0f;
//	
//	model = model_;
//
//	if (model) {
//		modelInstance = model->CreateInstance(position, angle, rotation, scale);
//		
//	}
//}

GameObject::GameObject(Model* model_, glm::vec3 position_)
{
	model = nullptr;
	model = model_;
	modelInstance = 0;
	position = glm::vec3();
	position = position_;

	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	
	scale = glm::vec3(1.0f);
	
	angle = 0.0f;

	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
	} 

	std::cout << "Min: " << glm::to_string(boundingBox.minVert) << ", Max: " << glm::to_string(boundingBox.maxVert) << std::endl;
	
}

GameObject::~GameObject()
{
	
	model = nullptr;
}

void GameObject::Render(Camera* camera_)
{
	//if there is model then render 
	if (model) {
		
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

std::string GameObject::GetTag() const
{
	return tag;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return BoundingBox();
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}
