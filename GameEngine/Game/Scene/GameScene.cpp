#include "GameScene.h"

GameScene::GameScene(): shape(nullptr)
{
}

GameScene::~GameScene()
{
	delete model;
	model = nullptr;
	delete shape;
	shape = nullptr;
	
	light = nullptr;
	//light[1] = nullptr;

}

bool GameScene::OnCreate()
{

	Debug::Info("Create game scene", "GameScene.cpp", __LINE__);

	MEngine::GetInstance()->SetCamera(new Camera());


	MEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	
	//LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	light = new LightSource();
	//light[1] = new LightSource();

	/*1st LIGHT*/
	light->setPosition(glm::vec3(1.0f, 0.0f, 1.4f));
	light->setAmbient(0.1f);
	light->setDiffuse(0.8f);
	light->setSpecular(0.7f);
	light->setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

	///*2nd LIGHT*/
	//light[1]->setPosition(glm::vec3(1.0f, 0.0f, 1.4f));
	//light[1]->setAmbient(0.1f);
	//light[1]->setDiffuse(0.8f);
	//light[1]->setSpecular(0.7f);
	//light[1]->setLightColor(glm::vec3(2.0f, 1.0f, 2.0f));

	


	MEngine::GetInstance()->GetCamera()->Addlight(light);
	//MEngine::GetInstance()->GetCamera()->Addlight(light[1]);

	TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "./Resources/Textures/CheckerboardTexture.png");



	//Create verticles for triangle
	//
	Vertex v;
	std::vector<Vertex> vertexList;
	//reserve(doesn't have to move in the actual vector in the memory)
	vertexList.reserve(36);
	{v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.583f, 0.771f, 0.014f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.609f, 0.115f, 0.436f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.327f, 0.483f, 0.844f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.822f, 0.569f, 0.201f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.435f, 0.602f, 0.223f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.310f, 0.747f, 0.185f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.597f, 0.770f, 0.761f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.559f, 0.436f, 0.730f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.359f, 0.583f, 0.152f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.483f, 0.596f, 0.789f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.559f, 0.861f, 0.639f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.195f, 0.548f, 0.859f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.014f, 0.184f, 0.576f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.771f, 0.328f, 0.970f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.406f, 0.615f, 0.116f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.676f, 0.977f, 0.133f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.971f, 0.572f, 0.833f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.140f, 0.616f, 0.489f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.997f, 0.513f, 0.064f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.945f, 0.719f, 0.592f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.543f, 0.021f, 0.978f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.279f, 0.317f, 0.505f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.167f, 0.620f, 0.077f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.347f, 0.857f, 0.137f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.055f, 0.953f, 0.042f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.714f, 0.505f, 0.345f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.783f, 0.290f, 0.734f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.722f, 0.645f, 0.174f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.302f, 0.455f, 0.848f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.225f, 0.587f, 0.040f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.517f, 0.713f, 0.338f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.053f, 0.959f, 0.120f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.393f, 0.621f, 0.362f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.673f, 0.211f, 0.457f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.820f, 0.883f, 0.371f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.textureCoordinates = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.982f, 0.099f, 0.879f);
	vertexList.push_back(v);
}
	

//color
	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"));
	//create new mesh pass in vertexlist
	//get 3 meshes verticle to Mesh contructor 
	//then pass entire mesh object to model
	model->AddMesh(new Mesh(vertexList, TextureHandler::GetInstance()->GetTexture("CheckerboardTexture"),
		ShaderHandler::GetInstance()->GetShader("basicShader")));
	//model->SetScale(glm::vec3(0.5f));

	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	model->SetAngle(model->GetAngle() + 0.01f);
	model->SetRotation(glm::vec3(1.0f, 1.0f, 1.0f));
	
	
}

void GameScene::Render()
{
	shape->Render(MEngine::GetInstance()->GetCamera());
	
}
