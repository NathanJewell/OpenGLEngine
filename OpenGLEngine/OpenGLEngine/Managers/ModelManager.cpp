//ModelManager.cpp
#include "ModelManager.h"

using namespace Managers;

ModelManager::ModelManager()
{
	//Rendering::Models::Triangle* triangle = new Rendering::Models::Triangle();
	/*
	Rendering::Models::Cube* cube = new Rendering::Models::Cube();
	cube->SetProgram(Managers::ShaderManager::GetShader("rotationShader"));
	cube->Create();
	gameModelList["cube"] = cube;
	*/

	Rendering::Models::LoadedModel* cube = new Rendering::Models::LoadedModel();
	cube->SetProgram(Managers::ShaderManager::GetShader("lightingShader"));
	//cube->setTextureString("C:\\Users\\Nathan\\Desktop\\OpenGLEngine\\OpenGLEngine\\OpenGLEngine\\Rendering\\Models\\cube.bmp");
	//cube->Create("C:\\Users\\Nathan\\Desktop\\OpenGLEngine\\OpenGLEngine\\OpenGLEngine\\Rendering\\Models\\monkey.obj");
	cube->Create("..\\OpenGLEngine\\Rendering\\Models\\uvCube.obj");
	gameModelList["cube"] = cube;

}

ModelManager::~ModelManager()
{
	for (auto model : gameModelList) //iterate through object array and delete stuff
	{
		delete model.second;
	}

	gameModelList.clear();

}

void ModelManager::DeleteModel(const std::string& modelName)
{
	if (gameModelList.count(modelName) > 0) //if the model exists
	{
		Rendering::GameObject* model = gameModelList[modelName];
		model->Destroy();
		gameModelList.erase(modelName);
	}
	else
	{
		//model does not exist and cannot be deleted
		std::cout << "ModelManager ERROR:\tin DeleteModel()...\n\tThe requested model " << modelName << " does not exist and could not be deleted.\n";
	}
	
}

const Rendering::GameObject& ModelManager::getModel(const std::string& modelName) const
{
	if (gameModelList.count(modelName) > 0) //make sure model exists
	{
		return (*gameModelList.at(modelName));
	}
	else //error model not found
	{
		std::cout << "ModelManager ERROR:\tin GetModel()...\n\tThe requested model " << modelName << " does not exist.\n";
	}
}

void ModelManager::Update()
{
	for (auto model : gameModelList)
	{
		model.second->Update();
	}
}

void ModelManager::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	for (auto model : gameModelList)
	{
		model.second->Draw(projectionMatrix, viewMatrix);
	}
}